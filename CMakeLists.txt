cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(tetris LANGUAGES CXX)

find_package(SFML 3.0.0 COMPONENTS Graphics Audio Network System REQUIRED)

add_executable(tetris src/main.cpp)

target_include_directories(tetris PRIVATE inc)

target_link_libraries(tetris PRIVATE sfml-graphics sfml-system)

target_compile_options(tetris PRIVATE -Werror -Wall -Wextra -pedantic)

target_compile_features(tetris PRIVATE cxx_std_23)

