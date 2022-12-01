cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME AdventOfCode)
project(${PROJECT_NAME} VERSION 2022)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
add_executable(day1 "${CMAKE_CURRENT_SOURCE_DIR}/src/day1.cpp")
add_executable(day1_2 "${CMAKE_CURRENT_SOURCE_DIR}/src/day1_2.cpp")

set_target_properties(day1 PROPERTIES OUTPUT_NAME "aoc")
set_target_properties(day1_2 PROPERTIES OUTPUT_NAME "aoc")