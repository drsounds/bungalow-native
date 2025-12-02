cmake_minimum_required(VERSION 3.10)
project(SpacifyClient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
cmake_policy(Boost REQUIRED)
find_package(Lua REQUIRED)
set(wxWidgets_USE_LIBS "")
find_package(WxWidgets REQUIRED)

# Include directories
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${wxWidgets_INCLUDE_DIRS})
include_directories(include)

# Source files
file(GLOB SOURCES "spider/src/*.cpp")
file(GLOB HEADERS "spider/include/*.h")

if(WIN32)
    file(GLOB SOURCES "windows/src/*.cpp")
    file(GLOB HEADERS "windows/src/*.h")
else()
    file(GLOB SOURCES "wxwidgets/src/*.cpp")
    file(GLOB HEADERS "wxwidgets/include/*.h")
endif()

# Executable
add_executable(spacify-client ${SOURCES} ${HEADERS} ${WX_SOURCES} ${WX_HEADERS})

# Link libraries
target_link_libraries(spacify-client ${LUA_LIBRARIES} ${wxWidgets_LIBRARIES})

# Platform specific configuration
if(WIN32)
    target_link_libraries(spacify-client gdi32 user32 kernel32 wxwidgets)
endif()