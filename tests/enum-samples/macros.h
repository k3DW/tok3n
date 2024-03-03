#pragma once

#define ASSERT_ALL_SAMPLES_IMPL(R, DATA, ELEM) \
	DATA(ELEM)

#define ASSERT_ALL_SAMPLES(ASSERTER)                                                                                                              \
	{                                                                                                                                             \
		BOOST_PP_SEQ_FOR_EACH(ASSERT_ALL_SAMPLES_IMPL, ASSERTER, BASIC_SAMPLES) \
	} REQUIRE_SEMICOLON



#define ASSERT_ALL_SAMPLES_2_EXPAND(ELEM1) \
	ELEM1, IDENTITY

#define ASSERT_ALL_SAMPLES_2_IMPL(r, product) \
	(ASSERT_ALL_SAMPLES_2_EXPAND product)

// This macro needs to be manually expanded in this ugly way otherwise it crashes the compiler
#define ASSERT_ALL_SAMPLES_2(ASSERTER)                                                                                      \
	{                                                                                                                       \
		IDENTITY(BOOST_PP_SEQ_FOR_EACH_PRODUCT(ASSERTER ASSERT_ALL_SAMPLES_2_IMPL, (BASIC_SAMPLES)(BASIC_SAMPLES)))         \
	} REQUIRE_SEMICOLON