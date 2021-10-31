cmake_minimum_required(VERSION 3.11)

project(tests)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL                 https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
    URL_HASH            MD5=52943a59cefce0ae0491d4d2412c120b
)
FetchContent_GetProperties(googletest)
if(NOT ${googletest_POPULATED})
    message(STATUS "fetching googletest ...")
    FetchContent_Populate(googletest)
endif()
mark_as_advanced(${googletest_SOURCE_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
file(
    GLOB
    SOURCES #
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" #
)

enable_testing()

add_executable(unittests ${SOURCES})
target_link_libraries(unittests 
    PUBLIC mathlib
    PUBLIC gtest_main
)

include(GoogleTest)
gtest_discover_tests(unittests)