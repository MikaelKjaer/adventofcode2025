cmake_minimum_required (VERSION 4.0)

message("-- CMake version: " "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project ("adventofcode2025" LANGUAGES CXX)

include(FetchContent)
include(day_utility)

setup_day_flags()
find_package(Threads REQUIRED)

file(GLOB TEST_INPUT_FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/input/*.txt)
file(COPY ${TEST_INPUT_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/input)

add_subdirectory("utility")
add_subdirectory("day01")
add_subdirectory("day02")
add_subdirectory("day03")
add_subdirectory("day04")
add_subdirectory("day05")
add_subdirectory("day06")
add_subdirectory("day07")
add_subdirectory("day08")
add_subdirectory("day09")
add_subdirectory("day10")
add_subdirectory("day11")
add_subdirectory("day12")
