cmake_minimum_required(VERSION 3.11)

project(mathlib)

set (CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

option(BUILD_TESTS "Build Unittests" OFF)

if(${BUILD_TESTS})
    add_subdirectory(tests)
endif(${BUILD_TESTS})
