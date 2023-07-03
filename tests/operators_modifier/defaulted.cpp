#include "pch.h"

static void prefix()
{
	assert
		, def1 == defaulted<int>(+abc)
		, def2 == defaulted<Class3>(~(abc | qq))
		;
}

static void infix()
{
	assert
		, def1 == +abc % defaulted<int>
		, def2 == ~(abc | qq) % defaulted<Class3>
		;
}



constexpr auto defaulted_checker = []<Parser P>(P) -> bool
{
	TOK3N_ASSERT_P( requires { defaulted<bool>(P{}); },              "defaulted<bool> prefix operator doesn't compile, but it should" );
	TOK3N_ASSERT_P( defaulted<bool>(P{}) == (Defaulted<P, bool>{}),  "defaulted<bool> prefix operator of any other parser should give Defaulted parser of the argument" );
	TOK3N_ASSERT_P( requires { P{} % defaulted<bool>; },             "defaulted<bool> infix operator doesn't compile, but it should" );
	TOK3N_ASSERT_P( P{} % defaulted<bool> == (Defaulted<P, bool>{}), "defaulted<bool> infix operator of any other parser should give Defaulted parser of the argument" );

	return true;
};

static void defaulted_anything()
{
	assert
		, check_all_samples(defaulted_checker)
		;
}

void defaulted_tests()
{
	prefix();
	infix();
	defaulted_anything();
}
