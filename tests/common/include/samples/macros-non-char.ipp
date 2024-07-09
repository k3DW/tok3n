#include "samples/macros-common.ipp"

#define ASSERT_ALL_SAMPLES(ASSERTER) \
	ASSERT_SAMPLES(ASSERTER, BASIC_SAMPLES)

// This macro needs to be manually expanded in this ugly way otherwise it crashes the compiler
#define ASSERT_ALL_SAMPLES_2(ASSERTER)                            \
	{                                                             \
		ASSERT_SAMPLES_2(ASSERTER, BASIC_SAMPLES, BASIC_SAMPLES); \
	} REQUIRE_SEMICOLON
