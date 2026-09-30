cmake_minimum_required(VERSION 3.16)
include ( FetchContent )
project(Orbits LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_VERSION "3.1.0")
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        "${SFML_VERSION}"
)

FetchContent_MakeAvailable(SFML)

add_executable(orbits
    src/main.cpp
    src/Vector2D.cpp
    src/Body.cpp
)

target_include_directories(orbits PRIVATE src)
target_link_libraries(orbits PRIVATE SFML::Graphics)
target_compile_options(orbits PRIVATE -Wall -Wextra -Wpedantic)
