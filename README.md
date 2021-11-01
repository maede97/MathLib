# MathLib - Header-Only Templated Vector Library in C++
[![Unittests](https://github.com/maede97/MathLib/actions/workflows/test.yml/badge.svg)](https://github.com/maede97/MathLib/actions/workflows/test.yml)
[![Documentation](https://github.com/maede97/MathLib/actions/workflows/docs.yml/badge.svg)](https://github.com/maede97/MathLib/actions/workflows/docs.yml)

## Setup
Put the following lines into your CMake project:
```
cmake_minimum_required(VERSION 3.11)

include(FetchContent)
FetchContent_Declare(
    mathlib
    GIT_REPOSITORY     https://github.com/maede97/MathLib.git
    GIT_TAG            master
)
FetchContent_GetProperties(mathlib)
if(NOT ${mathlib_POPULATED})
    message(STATUS "fetching mathlib ...")
    FetchContent_Populate(mathlib)
endif()
mark_as_advanced(${mathlib_SOURCE_DIR})
add_subdirectory(${mathlib_SOURCE_DIR})

# Link to your executable
target_link_libraries(YOUR_EXECUTABLE PUBLIC mathlib)
```

## Example
```
#include <mathlib/mathlib.h>
#include <iostream>

int main()
{
    Vector3d v1(1.0);
    Vector3d v2(1.0, 2.0, 3.0);

    std::cout << v1 + v2 << std::endl; // 2 3 4

    std::cout << v1.cross(v2) << std::endl; // 1 -2 1

    Vector<6, double> v3;
    v3 << 1.5, 2.5, 3.5, 1.0, 2.0, 3.0;

    bool compare_v1_v2 = (v1 == v2);
    std::cout << compare_v1_v2 << std::endl; // 0

    bool compare_v2_v3a = (v3.tail<3>() == v2);
    std::cout << compare_v2_v3a << std::endl; // 1

    Vector<6, double> half(0.5);
    bool compare_v2_v3b = ((v3.head<3>() - half.segment<1, 3>()) == v2);
    std::cout << compare_v2_v3b << std::endl; // 1

    return 0;
}
```

## Documentation
Run doxygen on the doxygen file which can be found in the `docs` folder.
A hosted online version can be found [here](https://maede97.github.io/MathLib/).

## Unittests
Run CMake with `-DMATHLIB_BUILD_TESTS=ON`, then execute the build binary `./tests/unittests`.