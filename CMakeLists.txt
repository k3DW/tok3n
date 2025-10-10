# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required (VERSION 3.23)

project (k3_tok3n
         VERSION 0
         LANGUAGES CXX)

set(TOK3N_BUILD_TESTS OFF CACHE BOOL "Build tests")
set(TOK3N_DISCOVER_TESTS OFF CACHE BOOL "Add all tests to CTest")
set(TOK3N_BUILD_EXAMPLES OFF CACHE BOOL "Build examples")
set(TOK3N_BUILD_EXE OFF CACHE BOOL "Build tok3n's main() function")

set(TOK3N_CXX_STANDARD "" CACHE STRING "C++ standard to use")
set(TOK3N_CXX_WARNINGS "" CACHE STRING "C++ compiler warnings to enable")

if (TOK3N_CXX_STANDARD)
    include(cmake/standard/${TOK3N_CXX_STANDARD}.cmake)
endif()
if (TOK3N_CXX_WARNINGS)
    include(cmake/warnings/${TOK3N_CXX_WARNINGS}.cmake)
endif()



set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(include)
target_sources(k3_tok3n INTERFACE
    "$<$<CXX_COMPILER_ID:MSVC>:${CMAKE_CURRENT_LIST_DIR}/extra/tok3n.natvis>"
)

if (TOK3N_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if (TOK3N_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (TOK3N_BUILD_EXE)
    add_subdirectory(src)
endif()
