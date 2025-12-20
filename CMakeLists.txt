cmake_minimum_required(VERSION 3.10)
project(SpacifyClient)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SourceFiles wxwidgets/src/*.cpp space/src/*.cpp spacify/src/*.cpp)
# Find dependencies
find_package(Boost REQUIRED)
find_package(Lua REQUIRED)
find_package(wxWidgets REQUIRED)
find_package(PNG REQUIRED)

find_package(EXPAT 2.2.8 MODULE REQUIRED)

# Include directories
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${wxWidgets_INCLUDE_DIRS})
include_directories(${FFI_INCLUDE_DIRS})
include_directories(${PNG_INCLUDE_DIRS})
include_directories(include)
set(CMAKE_BUILD_TYPE Debug)

if(WIN32)
    file(GLOB SOURCES "spacify/src/*.cpp" "space/src/*.cpp" "windows/src/*.cpp")
    file(GLOB HEADERS "spacify/include/*.h" "space/include/*.h" "windows/include/*.h")
else()
    file(GLOB SOURCES "spacify/src/*.cpp" "space/src/*.cpp" "wxwidgets/src/*.cpp")
    file(GLOB HEADERS "spacify/include/*.h" "space/include/*.h" "wxwidgets/include/*.h")
    include_directories(spacify/include space/include wxwidgets/include)
endif()
# Executable
add_executable(spacify-client ${SOURCES} ${HEADERS})

add_custom_target(debug_mode
    COMMAND python3 ${CMAKE_SOURCE_DIR}/launcher.py $<TARGET_FILE:spacify-client>
    DEPENDS my_app
)
set(CMAKE_PREFIX_PATH ="/opt/homebrew/opt/expat")
set(CMAKE_PKG_CONFIG_PC_PATH "/opt/homebrew/opt/expat/lib/pkgconfig")
set(CMAKE_LINK_DEF_FILE_FLAG "-L/opt/homebrew/opt/expat/lib")
set(CMAKE_CXX_FLAGS "-I/opt/homebrew/lib/wx/include/osx_cocoa-unicode-3.3 -I/opt/homebrew/include/wx-3.3 -I/opt/homebrew/opt/expat/include -D_FILE_OFFSET_BITS=64 -DwxDEBUG_LEVEL=0 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__ ")

# Link libraries
target_link_libraries(spacify-client ${EXPAT_LIBRARIES} ${LUA_LIBRARIES} ${wxWidgets_LIBRARIES} ${PNG_LIBRARY})

# Platform specific configuration
if(WIN32)
    target_link_libraries(spacify-client gdi32 user32 kernel32 wxwidgets)
endif()