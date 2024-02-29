cmake_minimum_required(VERSION 3.25)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(minesweeper main.cpp board.cpp cell.cpp sprites.cpp leaderboard.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR E:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(e:/SFML/include/SFML)

target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio)
