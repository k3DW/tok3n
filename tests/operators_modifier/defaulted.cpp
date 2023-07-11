#include "pch.h"

TEST("defaulted modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(def1, defaulted<int>(+abc));
	ASSERT_PARSER_VALUES_EQ(def2, defaulted<Class3>(~(abc | qq)));
}

TEST("defaulted modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(def1, +abc % defaulted<int>);
	ASSERT_PARSER_VALUES_EQ(def2, ~(abc | qq) % defaulted<Class3>);
}



constexpr auto defaulted_checker = []<Parser P>(P) -> bool
{
	TOK3N_ASSERT_P( requires { defaulted<bool>(P{}); },              "defaulted<bool> prefix operator doesn't compile, but it should" );
	TOK3N_ASSERT_P( defaulted<bool>(P{}) == (Defaulted<P, bool>{}),  "defaulted<bool> prefix operator of any other parser should give Defaulted parser of the argument" );
	TOK3N_ASSERT_P( requires { P{} % defaulted<bool>; },             "defaulted<bool> infix operator doesn't compile, but it should" );
	TOK3N_ASSERT_P( P{} % defaulted<bool> == (Defaulted<P, bool>{}), "defaulted<bool> infix operator of any other parser should give Defaulted parser of the argument" );

	return true;
};

TEST("defaulted modifier", "modify anything")
{
	ASSERT(check_all_samples(defaulted_checker), "check_all_samples(defaulted_checker) failed");
}
