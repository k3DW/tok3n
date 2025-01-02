// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include "samples.hpp"

#define ASSERT_SAMPLES_IMPL_(R, DATA, ELEM) \
	DATA(ELEM)

#define ASSERT_SAMPLES(ASSERTER, SAMPLES)                              \
	{                                                                  \
		BOOST_PP_SEQ_FOR_EACH(ASSERT_SAMPLES_IMPL_, ASSERTER, SAMPLES) \
	} REQUIRE_SEMICOLON



#define ASSERT_SAMPLES_2_EXPAND_(ELEM1) \
	ELEM1, IDENTITY

#define ASSERT_SAMPLES_2_IMPL_(r, product) \
	(ASSERT_SAMPLES_2_EXPAND_ product)

#define ASSERT_SAMPLES_2_IDENTITY_(...) __VA_ARGS__

#define ASSERT_SAMPLES_2(ASSERTER, SAMPLES_LHS, SAMPLES_RHS) \
	{                                                        \
		ASSERT_SAMPLES_2_IDENTITY_(                          \
			BOOST_PP_SEQ_FOR_EACH_PRODUCT(                   \
				ASSERTER ASSERT_SAMPLES_2_IMPL_,             \
				(SAMPLES_LHS)(SAMPLES_RHS)                   \
			)                                                \
		)                                                    \
	} REQUIRE_SEMICOLON
