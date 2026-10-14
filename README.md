# Spacify Client

Spacify Client is a C++ desktop application which aims to be a fast decentralized media player based on services.

It uses an own written GUI framework called **Space** which is a lightweight abstract GUI framework that aims to create an alternate protocol for serving content over the internet

## Building

Build dependencies include CMake, a C++17 compiler, Boost, Lua, libpng, Expat, and wxWidgets. The native Windows backends use wxWidgets' base library for XML parsing, but do not use its GUI toolkit.

The UI backend is selected with `BUNGALOW_UI_BACKEND`:

```bash
cmake -S . -B build -DBUNGALOW_UI_BACKEND=wxwidgets
cmake --build build
```

On Windows, `win32` selects the native Win32 host; `wtl` selects a WTL host and additionally requires WTL headers. Set `WTL_INCLUDE_DIR` to the directory containing `atlapp.h`.

```powershell
cmake -S . -B build -DBUNGALOW_UI_BACKEND=win32
cmake --build build --config Release
```

The three Windows release workflows in GitHub Actions can be started manually. Each builds and uploads a ZIP artifact and attaches it to the release tag supplied when starting the workflow.

## Usage

TBA

## License

MIT
