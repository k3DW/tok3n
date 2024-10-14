// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples/macros-common.ipp"

#define ASSERT_ALL_SAMPLES(ASSERTER) \
	ASSERT_SAMPLES(ASSERTER, BASIC_SAMPLES)

// This macro needs to be manually expanded in this ugly way otherwise it crashes the compiler
#define ASSERT_ALL_SAMPLES_2(ASSERTER)                            \
	{                                                             \
		ASSERT_SAMPLES_2(ASSERTER, BASIC_SAMPLES, BASIC_SAMPLES); \
	} REQUIRE_SEMICOLON
