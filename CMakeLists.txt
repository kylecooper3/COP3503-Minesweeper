cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

# main.cpp pulls in the other source files with #include, so it is the only
# file compiled directly.
add_executable(minesweeper main.cpp)

# Point CMake at your SFML install with -DSFML_DIR=<SFML>/lib/cmake/SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio)
