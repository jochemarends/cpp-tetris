cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(tetris LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)

FetchContent_MakeAvailable(sfml)

add_executable(tetris src/main.cpp)

target_sources(tetris PRIVATE src/game.cpp src/level.cpp)

target_include_directories(tetris PRIVATE inc)

target_link_libraries(tetris PRIVATE sfml-system sfml-window sfml-graphics)

target_compile_options(tetris PRIVATE -Werror -Wall -Wextra -pedantic)

target_compile_features(tetris PRIVATE cxx_std_23)

