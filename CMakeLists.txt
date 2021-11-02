cmake_minimum_required(VERSION 3.11)

project(mathlib)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "include/mathlib/*.h")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

target_sources(${PROJECT_NAME} INTERFACE ${SOURCES})

option(MATHLIB_BUILD_TESTS "Build Unittests" OFF)

if(${MATHLIB_BUILD_TESTS})
    add_subdirectory(tests)
endif(${MATHLIB_BUILD_TESTS})
