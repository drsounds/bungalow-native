cmake_minimum_required(VERSION 3.10)
project(SpacifyClient)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(Boost REQUIRED)
find_package(Lua REQUIRED)
find_package(wxWidgets REQUIRED)

# Include directories
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${wxWidgets_INCLUDE_DIRS})
include_directories(include)

if(WIN32)
    file(GLOB SOURCES "spacify/src/*.cpp" "spider/src/*.cpp" "windows/src/*.cpp")
    file(GLOB HEADERS "spacify/include/*.h" "spider/include/*.h" "windows/include/*.h")
else()
    file(GLOB SOURCES "spacify/src/*.cpp" "spider/src/*.cpp" "wxwidgets/src/*.cpp")
    file(GLOB HEADERS "spacify/include/*.h" "spider/include/*.h" "wxwidgets/include/*.h")
    include_directories(spacify/include spider/include wxwidgets/include)
endif()
# Executable
add_executable(spacify-client ${SOURCES} ${HEADERS})


set(CMAKE_CXX_FLAGS "-I/opt/homebrew/lib/wx/include/osx_cocoa-unicode-3.3 -I/opt/homebrew/include/wx-3.3 -D_FILE_OFFSET_BITS=64 -DwxDEBUG_LEVEL=0 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__")

# Link libraries
target_link_libraries(spacify-client ${LUA_LIBRARIES} ${wxWidgets_LIBRARIES})

# Platform specific configuration
if(WIN32)
    target_link_libraries(spacify-client gdi32 user32 kernel32 wxwidgets)
endif()