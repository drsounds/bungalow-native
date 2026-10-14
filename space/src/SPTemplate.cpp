#include "SPTemplate.h"

extern "C" {
#include <lauxlib.h>
#include <lualib.h>
#include <lua.h>
}

#include <cctype>
#include <fstream>
#include <memory>
#include <regex>
#include <sstream>
#include <stdexcept>

namespace space {
    namespace {
        std::string trim(const std::string& value) {
            const auto first = value.find_first_not_of(" \t\n\r\f\v");
            if (first == std::string::npos) {
                return "";
            }
            const auto last = value.find_last_not_of(" \t\n\r\f\v");
            return value.substr(first, last - first + 1);
        }

        std::string trimLeading(const std::string& value) {
            const auto first = value.find_first_not_of(" \t\n\r\f\v");
            return first == std::string::npos ? "" : value.substr(first);
        }

        std::string quote(const std::string& value) {
            std::ostringstream quoted;
            quoted << '"';
            for (const unsigned char c : value) {
                switch (c) {
                    case '\\': quoted << "\\\\"; break;
                    case '"': quoted << "\\\""; break;
                    case '\n': quoted << "\\n"; break;
                    case '\r': quoted << "\\r"; break;
                    case '\t': quoted << "\\t"; break;
                    default:
                        if (c < 32 || c == 127) {
                            quoted << '\\';
                            quoted.width(3);
                            quoted.fill('0');
                            quoted << static_cast<unsigned int>(c);
                        } else {
                            quoted << static_cast<char>(c);
                        }
                }
            }
            quoted << '"';
            return quoted.str();
        }

        void emitLiteral(std::string& output, const std::string& value) {
            if (!value.empty()) {
                output += " __emit(" + quote(value) + ")";
            }
        }

        std::string compileTextLine(const std::string& line) {
            std::string output;
            std::size_t position = 0;
            while (position < line.size()) {
                const auto open = line.find("${", position);
                if (open == std::string::npos) {
                    emitLiteral(output, line.substr(position));
                    break;
                }
                const auto close = line.find('}', open + 2);
                if (close == std::string::npos) {
                    emitLiteral(output, line.substr(position));
                    break;
                }
                emitLiteral(output, line.substr(position, open - position));
                const auto expression = trim(line.substr(open + 2, close - open - 2));
                output += " __emit(__str(" + expression + "))";
                position = close + 1;
            }
            emitLiteral(output, "\n");
            return output;
        }

        std::string compileCodeLine(const std::string& code) {
            static const std::regex countLoop(
                R"(^\s*for\s+([A-Za-z_]\w*)\s*,\s*(.+?)\s+do\s*$)");
            std::smatch match;
            if (std::regex_match(code, match, countLoop)) {
                return "for " + match[1].str() + "=1," + trim(match[2].str()) + " do";
            }
            return trim(code);
        }

        std::string compile(const std::string& source) {
            std::string output =
                "local __out = {}\n"
                "local function __emit(s) __out[#__out + 1] = s end\n"
                "local function __str(v) if v == nil then return \"\" end return tostring(v) end\n";

            std::size_t start = 0;
            do {
                const auto end = source.find('\n', start);
                const auto line = source.substr(start, end == std::string::npos ? end : end - start);
                const auto leadingTrimmed = trimLeading(line);
                if (!leadingTrimmed.empty() && leadingTrimmed.front() == '%') {
                    output += compileCodeLine(leadingTrimmed.substr(1)) + "\n";
                } else {
                    output += compileTextLine(line) + "\n";
                }
                if (end == std::string::npos) {
                    break;
                }
                start = end + 1;
            } while (start <= source.size());

            output += "return table.concat(__out)\n";
            return output;
        }

        void pushJson(lua_State* state, const boost::json::value& value) {
            switch (value.kind()) {
                case boost::json::kind::null:
                    lua_pushnil(state);
                    break;
                case boost::json::kind::bool_:
                    lua_pushboolean(state, value.as_bool());
                    break;
                case boost::json::kind::int64:
                    lua_pushnumber(state, static_cast<lua_Number>(value.as_int64()));
                    break;
                case boost::json::kind::uint64:
                    lua_pushnumber(state, static_cast<lua_Number>(value.as_uint64()));
                    break;
                case boost::json::kind::double_:
                    lua_pushnumber(state, value.as_double());
                    break;
                case boost::json::kind::string: {
                    const auto& text = value.as_string();
                    lua_pushlstring(state, text.data(), text.size());
                    break;
                }
                case boost::json::kind::array: {
                    const auto& array = value.as_array();
                    lua_createtable(state, static_cast<int>(array.size()), 0);
                    lua_Integer index = 1;
                    for (const auto& item : array) {
                        pushJson(state, item);
                        lua_rawseti(state, -2, index++);
                    }
                    break;
                }
                case boost::json::kind::object: {
                    const auto& object = value.as_object();
                    lua_createtable(state, 0, static_cast<int>(object.size()));
                    for (const auto& item : object) {
                        lua_pushlstring(state, item.key().data(), item.key().size());
                        pushJson(state, item.value());
                        lua_settable(state, -3);
                    }
                    break;
                }
            }
        }

        void setString(lua_State* state, const char* name, const std::string& value) {
            lua_pushlstring(state, value.data(), value.size());
            lua_setglobal(state, name);
        }

        void setTable(lua_State* state, const char* name, const boost::json::object& value) {
            pushJson(state, value);
            lua_setglobal(state, name);
        }

        std::string luaError(lua_State* state) {
            const char* message = lua_tostring(state, -1);
            return message != nullptr ? message : "unknown Lua error";
        }
    }

    std::string SPTemplate::render(
        const std::string& source,
        const std::string& method,
        const std::string& uri,
        const std::string& action,
        const boost::json::object& data,
        const boost::json::object& model) {
        std::unique_ptr<lua_State, decltype(&lua_close)> state(luaL_newstate(), lua_close);
        if (!state) {
            throw std::runtime_error("Unable to create Lua state");
        }
        luaL_openlibs(state.get());
        setString(state.get(), "method", method);
        setString(state.get(), "uri", uri);
        setString(state.get(), "action", action);
        setTable(state.get(), "data", data);
        setTable(state.get(), "model", model);

        const auto luaSource = compile(source);
        if (luaL_loadbuffer(state.get(), luaSource.data(), luaSource.size(), "spacify-template") != LUA_OK) {
            throw std::runtime_error(luaError(state.get()));
        }
        if (lua_pcall(state.get(), 0, 1, 0) != LUA_OK) {
            throw std::runtime_error(luaError(state.get()));
        }
        std::size_t length = 0;
        const char* result = lua_tolstring(state.get(), -1, &length);
        if (result == nullptr) {
            throw std::runtime_error("Lua template did not return a string");
        }
        return std::string(result, length);
    }

    std::string SPTemplate::renderFile(
        const std::string& filename,
        const std::string& method,
        const std::string& uri,
        const std::string& action,
        const boost::json::object& data,
        const boost::json::object& model) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Unable to open template: " + filename);
        }
        std::ostringstream source;
        source << file.rdbuf();
        return render(source.str(), method, uri, action, data, model);
    }
}
