# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required (VERSION 3.23)

project (k3_tok3n
         VERSION 0
         LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(include)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_sources(k3_tok3n INTERFACE
        "$<$<CXX_COMPILER_ID:MSVC>:${CMAKE_CURRENT_LIST_DIR}/extra/tok3n.natvis>"
    )
endif()

option (TOK3N_BUILD_TESTS "Build tests" OFF)
option (TOK3N_DISCOVER_TESTS "Add all tests to CTest" OFF)

option (TOK3N_BUILD_EXAMPLES "Build examples" OFF)
option (TOK3N_BUILD_EXE "Build tok3n's main() function" OFF)



#--------------------------------------------
#   Shared settings
#--------------------------------------------
if (TOK3N_BUILD_TESTS OR TOK3N_BUILD_EXAMPLES OR TOK3N_BUILD_EXE)

    add_library(tok3n_shared_settings INTERFACE)
    target_link_libraries(tok3n_shared_settings INTERFACE k3::tok3n)

    set_target_properties(tok3n_shared_settings
        PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
    )

    target_compile_features(tok3n_shared_settings
        INTERFACE
            cxx_std_20
    )

    target_compile_options(tok3n_shared_settings INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:
            /permissive- /volatile:iso /Zc:preprocessor
            /WX /W4
            /w14640
            /w14242
            /w14254
            /w14263
            /w14265
            /w14287
            /we4289
            /w14296
            /w14311
            /w14545
            /w14546
            /w14547
            /w14549
            /w14555
            /w14619
            /w14640
            /w14826
            /w14905
            /w14906
            /w14928
        >
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
            -Werror
            -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
            -Wold-style-cast
            -Wcast-align
            -Wunused
            -Woverloaded-virtual
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wmisleading-indentation
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
            -Wimplicit-fallthrough
        >
        $<$<CXX_COMPILER_ID:GNU>:
            -Wduplicated-cond
            -Wduplicated-branches
            -Wlogical-op
            -Wuseless-cast
        >
    )

endif()



#--------------------------------------------
#   Tests
#--------------------------------------------
if (TOK3N_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()



#--------------------------------------------
#   Examples
#--------------------------------------------
if (TOK3N_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()



#--------------------------------------------
#   Main
#--------------------------------------------
if (TOK3N_BUILD_EXE)
    add_executable(tok3n_main "src/main.cpp")
    source_group("" FILES "src/main.cpp")
    target_link_libraries(tok3n_main tok3n_shared_settings)
endif()
