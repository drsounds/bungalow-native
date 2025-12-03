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
    file(GLOB SOURCES "spider/src/*.cpp" "windows/src/*.cpp")
    file(GLOB HEADERS "spider/include/*.h" "windows/include/*.h")
else()
    file(GLOB SOURCES "spider/src/*.cpp" "wxwidgets/src/*.cpp")
    file(GLOB HEADERS "spider/include/*.h" "wxwidgets/include/*.h")
    include_directories(spider/include wxwidgets/include)
endif()
# Executable
add_executable(spacify-client ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(spacify-client ${LUA_LIBRARIES} ${wxWidgets_LIBRARIES})

# Platform specific configuration
if(WIN32)
    target_link_libraries(spacify-client gdi32 user32 kernel32 wxwidgets)
endif()