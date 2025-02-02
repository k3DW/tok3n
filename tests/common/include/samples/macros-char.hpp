// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_SAMPLES_MACROS_CHAR_HPP
#define K3_TOK3N_TESTS_SAMPLES_MACROS_CHAR_HPP

#include "samples.hpp"
#include "samples/macros-common.hpp"


#define ASSERT_ALL_SAMPLES(ASSERTER) \
	ASSERT_SAMPLES(ASSERTER, ADAPTOR_SAMPLES BASIC_SAMPLES COMPOUND_SAMPLES DIVERGENT_SAMPLES REPEAT_SAMPLES)

// This macro needs to be manually expanded in this ugly way otherwise it crashes the compiler
#define ASSERT_ALL_SAMPLES_2(ASSERTER)                                    \
	{                                                                     \
		ASSERT_SAMPLES_2(ASSERTER, ADAPTOR_SAMPLES, ADAPTOR_SAMPLES);     \
		ASSERT_SAMPLES_2(ASSERTER, ADAPTOR_SAMPLES, BASIC_SAMPLES);       \
		ASSERT_SAMPLES_2(ASSERTER, ADAPTOR_SAMPLES, COMPOUND_SAMPLES);    \
		ASSERT_SAMPLES_2(ASSERTER, ADAPTOR_SAMPLES, DIVERGENT_SAMPLES);   \
		ASSERT_SAMPLES_2(ASSERTER, ADAPTOR_SAMPLES, REPEAT_SAMPLES);      \
		ASSERT_SAMPLES_2(ASSERTER, BASIC_SAMPLES, ADAPTOR_SAMPLES);       \
		ASSERT_SAMPLES_2(ASSERTER, BASIC_SAMPLES, BASIC_SAMPLES);         \
		ASSERT_SAMPLES_2(ASSERTER, BASIC_SAMPLES, COMPOUND_SAMPLES);      \
		ASSERT_SAMPLES_2(ASSERTER, BASIC_SAMPLES, DIVERGENT_SAMPLES);     \
		ASSERT_SAMPLES_2(ASSERTER, BASIC_SAMPLES, REPEAT_SAMPLES);        \
		ASSERT_SAMPLES_2(ASSERTER, COMPOUND_SAMPLES, ADAPTOR_SAMPLES);    \
		ASSERT_SAMPLES_2(ASSERTER, COMPOUND_SAMPLES, BASIC_SAMPLES);      \
		ASSERT_SAMPLES_2(ASSERTER, COMPOUND_SAMPLES, COMPOUND_SAMPLES);   \
		ASSERT_SAMPLES_2(ASSERTER, COMPOUND_SAMPLES, DIVERGENT_SAMPLES);  \
		ASSERT_SAMPLES_2(ASSERTER, COMPOUND_SAMPLES, REPEAT_SAMPLES);     \
		ASSERT_SAMPLES_2(ASSERTER, DIVERGENT_SAMPLES, ADAPTOR_SAMPLES);   \
		ASSERT_SAMPLES_2(ASSERTER, DIVERGENT_SAMPLES, BASIC_SAMPLES);     \
		ASSERT_SAMPLES_2(ASSERTER, DIVERGENT_SAMPLES, COMPOUND_SAMPLES);  \
		ASSERT_SAMPLES_2(ASSERTER, DIVERGENT_SAMPLES, DIVERGENT_SAMPLES); \
		ASSERT_SAMPLES_2(ASSERTER, DIVERGENT_SAMPLES, REPEAT_SAMPLES);    \
		ASSERT_SAMPLES_2(ASSERTER, REPEAT_SAMPLES, ADAPTOR_SAMPLES);      \
		ASSERT_SAMPLES_2(ASSERTER, REPEAT_SAMPLES, BASIC_SAMPLES);        \
		ASSERT_SAMPLES_2(ASSERTER, REPEAT_SAMPLES, COMPOUND_SAMPLES);     \
		ASSERT_SAMPLES_2(ASSERTER, REPEAT_SAMPLES, DIVERGENT_SAMPLES);    \
		ASSERT_SAMPLES_2(ASSERTER, REPEAT_SAMPLES, REPEAT_SAMPLES);       \
	} REQUIRE_SEMICOLON

#endif // K3_TOK3N_TESTS_SAMPLES_MACROS_CHAR_HPP
