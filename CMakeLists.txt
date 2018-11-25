cmake_minimum_required(VERSION 3.5)
project (minesweeper)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(minesweeper main.cpp logic.cpp renderer.cpp)

find_package(SFML COMPONENTS audio graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(minesweeper ${SFML_LIBRARIES})

target_link_libraries(minesweeper sfml-graphics)