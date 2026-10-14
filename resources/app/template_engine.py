import ctypes
import ctypes.util
import re
from collections.abc import Mapping
from pathlib import Path


class TemplateError(RuntimeError):
    pass


_COUNT_FOR = re.compile(r"^\s*for\s+([A-Za-z_]\w*)\s*,\s*(.+?)\s+do\s*$")
_VIEWS_DIR = Path(__file__).resolve().parent / "views"


def _lua_quote(value):
    escaped = ['"']
    for char in value:
        if char == '\\':
            escaped.append('\\\\')
        elif char == '"':
            escaped.append('\\"')
        elif char == '\n':
            escaped.append('\\n')
        elif char == '\r':
            escaped.append('\\r')
        elif char == '\t':
            escaped.append('\\t')
        elif ord(char) < 32:
            escaped.append('\\%03d' % ord(char))
        else:
            escaped.append(char)
    escaped.append('"')
    return ''.join(escaped)


def _compile_code_line(code):
    match = _COUNT_FOR.match(code)
    if match:
        return 'for %s=1,%s do' % (match.group(1), match.group(2).strip())
    return code.strip()


def _compile_text_line(line):
    output = []
    position = 0
    while position < len(line):
        opening = line.find('${', position)
        if opening < 0:
            if position < len(line):
                output.append('__emit(%s)' % _lua_quote(line[position:]))
            break
        closing = line.find('}', opening + 2)
        if closing < 0:
            output.append('__emit(%s)' % _lua_quote(line[position:]))
            break
        if opening > position:
            output.append('__emit(%s)' % _lua_quote(line[position:opening]))
        expression = line[opening + 2:closing].strip()
        output.append('__emit(__str(%s))' % expression)
        position = closing + 1
    output.append('__emit("\\n")')
    return ' '.join(output)


def compile_template(template):
    lua = [
        'local __out = {}',
        'local function __emit(s) __out[#__out + 1] = s end',
        'local function __str(v) if v == nil then return "" end return tostring(v) end',
    ]
    for line in template.split('\n'):
        trimmed = line.lstrip()
        if trimmed.startswith('%'):
            lua.append(_compile_code_line(trimmed[1:]))
        else:
            lua.append(_compile_text_line(line))
    lua.append('return table.concat(__out)')
    return '\n'.join(lua) + '\n'


def _find_lua_library():
    names = ('lua5.4', 'lua54', 'lua5.3', 'lua53', 'lua5.2', 'lua52', 'lua')
    for name in names:
        library = ctypes.util.find_library(name)
        if library:
            try:
                return ctypes.CDLL(library)
            except OSError:
                pass
    raise RuntimeError('Lua 5.2 or newer shared library is required')


class _LuaRuntime:
    def __init__(self):
        self.library = _find_lua_library()
        self._bind_api()

    def _bind_api(self):
        lib = self.library
        pointer = ctypes.c_void_p
        lib.luaL_newstate.restype = pointer
        lib.luaL_openlibs.argtypes = [pointer]
        lib.lua_close.argtypes = [pointer]
        lib.lua_gettop.argtypes = [pointer]
        lib.lua_gettop.restype = ctypes.c_int
        lib.lua_pushlstring.argtypes = [pointer, ctypes.c_char_p, ctypes.c_size_t]
        lib.lua_pushlstring.restype = pointer
        lib.lua_pushnil.argtypes = [pointer]
        lib.lua_pushnumber.argtypes = [pointer, ctypes.c_double]
        lib.lua_pushinteger.argtypes = [pointer, ctypes.c_longlong]
        lib.lua_pushboolean.argtypes = [pointer, ctypes.c_int]
        lib.lua_createtable.argtypes = [pointer, ctypes.c_int, ctypes.c_int]
        lib.lua_setfield.argtypes = [pointer, ctypes.c_int, ctypes.c_char_p]
        lib.lua_rawseti.argtypes = [pointer, ctypes.c_int, ctypes.c_longlong]
        lib.lua_setglobal.argtypes = [pointer, ctypes.c_char_p]
        lib.lua_tolstring.argtypes = [pointer, ctypes.c_int, ctypes.POINTER(ctypes.c_size_t)]
        lib.lua_tolstring.restype = pointer
        lib.luaL_loadbufferx.argtypes = [
            pointer, ctypes.c_char_p, ctypes.c_size_t, ctypes.c_char_p, ctypes.c_char_p,
        ]
        lib.luaL_loadbufferx.restype = ctypes.c_int
        if hasattr(lib, 'lua_pcallk'):
            lib.lua_pcallk.argtypes = [
                pointer, ctypes.c_int, ctypes.c_int, ctypes.c_int,
                ctypes.c_longlong, pointer,
            ]
            lib.lua_pcallk.restype = ctypes.c_int
            self._protected_call = lambda state: lib.lua_pcallk(state, 0, 1, 0, 0, None)
        else:
            lib.lua_pcall.argtypes = [pointer, ctypes.c_int, ctypes.c_int, ctypes.c_int]
            lib.lua_pcall.restype = ctypes.c_int
            self._protected_call = lambda state: lib.lua_pcall(state, 0, 1, 0)

    def _push_value(self, state, value):
        lib = self.library
        if value is None:
            lib.lua_pushnil(state)
        elif isinstance(value, bool):
            lib.lua_pushboolean(state, int(value))
        elif isinstance(value, int):
            lib.lua_pushinteger(state, value)
        elif isinstance(value, float):
            lib.lua_pushnumber(state, value)
        elif isinstance(value, Mapping):
            lib.lua_createtable(state, 0, len(value))
            table_index = lib.lua_gettop(state)
            for key, item in value.items():
                self._push_value(state, item)
                lib.lua_setfield(state, table_index, str(key).encode('utf-8'))
        elif isinstance(value, (list, tuple)):
            lib.lua_createtable(state, len(value), 0)
            table_index = lib.lua_gettop(state)
            for index, item in enumerate(value, start=1):
                self._push_value(state, item)
                lib.lua_rawseti(state, table_index, index)
        else:
            encoded = str(value).encode('utf-8')
            lib.lua_pushlstring(state, encoded, len(encoded))

    def _error(self, state):
        length = ctypes.c_size_t()
        value = self.library.lua_tolstring(state, -1, ctypes.byref(length))
        if not value:
            return 'unknown Lua error'
        return ctypes.string_at(value, length.value).decode('utf-8', 'replace')

    def render(self, source, name, context):
        state = self.library.luaL_newstate()
        if not state:
            raise TemplateError('Could not create Lua state')
        try:
            self.library.luaL_openlibs(state)
            bindings = {
                'method': 'GET',
                'uri': '',
                'action': '',
                'data': {},
                'model': {},
            }
            bindings.update(context)
            if bindings['model'] is None:
                bindings['model'] = {}
            for key, value in bindings.items():
                self._push_value(state, value)
                self.library.lua_setglobal(state, str(key).encode('utf-8'))

            encoded = source.encode('utf-8')
            status = self.library.luaL_loadbufferx(
                state, encoded, len(encoded), name.encode('utf-8'), None,
            )
            if status:
                raise TemplateError('Lua template compilation failed in %s: %s' % (name, self._error(state)))
            status = self._protected_call(state)
            if status:
                raise TemplateError('Lua template execution failed in %s: %s' % (name, self._error(state)))

            length = ctypes.c_size_t()
            result = self.library.lua_tolstring(state, -1, ctypes.byref(length))
            if not result:
                raise TemplateError('Lua template in %s did not return markup' % name)
            return ctypes.string_at(result, length.value).decode('utf-8')
        finally:
            self.library.lua_close(state)


_runtime = None


def _get_runtime():
    global _runtime
    if _runtime is None:
        _runtime = _LuaRuntime()
    return _runtime


def render_string(template, context=None, name='template'):
    return _get_runtime().render(
        compile_template(template), name, dict(context or {}),
    )


def render_template(filename, **context):
    root = _VIEWS_DIR.resolve()
    path = (root / filename).resolve()
    if not path.is_relative_to(root):
        raise TemplateError('Template path is outside the views directory: %s' % filename)
    try:
        source = path.read_text(encoding='utf-8')
    except OSError as error:
        raise TemplateError('Could not read template %s: %s' % (filename, error)) from error
    return render_string(source, context, str(path))
