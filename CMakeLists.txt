cmake_minimum_required(VERSION 3.11)

project(mathlib)

set (CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

add_executable(example example.cpp)
target_link_libraries(example ${PROJECT_NAME})
