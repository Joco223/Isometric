cmake_minimum_required(VERSION 3.17)
project(Isometric)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 20)
set(SFML_DIR ../Libraries/SFML-2.5.1/lib/cmake/SFML)
set(SFML_STATIC_LIBRARIES TRUE)

include_directories(include)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Isometric source/main.cpp include/Rendering.h include/world_tile.h source/Rendering.cpp include/world_chunk.h include/SimplexNoise.h source/SimplexNoise.cpp source/world_chunk.cpp)
target_link_libraries(Isometric sfml-graphics sfml-audio)