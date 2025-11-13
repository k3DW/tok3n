// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_SAMPLES_MACROS_NON_CHAR_HPP
#define K3_TOK3N_TESTS_SAMPLES_MACROS_NON_CHAR_HPP

#include "samples.hpp"
#include "samples/macros-common.hpp"

// This macro needs to be manually expanded in this ugly way otherwise it crashes the compiler
#define ASSERT_ALL_SAMPLES_2(ASSERTER)                            \
    {                                                             \
        ASSERT_SAMPLES_2(ASSERTER, BASIC_SAMPLES, BASIC_SAMPLES); \
    } REQUIRE_SEMICOLON

#endif // K3_TOK3N_TESTS_SAMPLES_MACROS_NON_CHAR_HPP
