#include "pch.h"

TEST("constant modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(con1, constant<1>(+abc));
	ASSERT_PARSER_VALUES_EQ(con2, constant<'t'>(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(con3, constant<true>(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(con4, constant<nullptr>(+abc >> ~(abc | qq)));
}

TEST("constant modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(con1, +abc % constant<1>);
	ASSERT_PARSER_VALUES_EQ(con2, ~(abc | qq) % constant<'t'>);
	ASSERT_PARSER_VALUES_EQ(con3, (abc >> *qq) % constant<true>);
	ASSERT_PARSER_VALUES_EQ(con4, (+abc >> ~(abc | qq)) % constant<nullptr>);
}



constexpr auto constant_checker = []<Parser P>(P) -> bool
{
	TOK3N_ASSERT_P( requires { constant<0>(P{}); },          "constant<0> prefix operator doesn't compile, but it should" );
	TOK3N_ASSERT_P( constant<0>(P{}) == (Constant<P, 0>{}),  "constant<0> prefix operator of any other parser should give Constant parser of the argument" );
	TOK3N_ASSERT_P( requires { P{} % constant<0>; },         "constant<0> infix operator doesn't compile, but it should" );
	TOK3N_ASSERT_P( P{} % constant<0> == (Constant<P, 0>{}), "constant<0> infix operator of any other parser should give Constant parser of the argument" );

	return true;
};

TEST("constant modifier", "modify anything")
{
	ASSERT(check_all_samples(constant_checker), "check_all_samples(constant_checker) failed");
}
