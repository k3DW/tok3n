#include "pch.h"

TEST("exactly modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(exa1, exactly<3>(l1));
	ASSERT_PARSER_VALUES_EQ(exa2, exactly<5>(oc1));
	ASSERT_PARSER_VALUES_EQ(exa3, exactly<4>(l1 | oc1));
	ASSERT_PARSER_VALUES_EQ(exa4, exactly<2>(l1 >> oc1));
}

TEST("exactly modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(exa1, l1 % exactly<3>);
	ASSERT_PARSER_VALUES_EQ(exa2, oc1 % exactly<5>);
	ASSERT_PARSER_VALUES_EQ(exa3, (l1 | oc1) % exactly<4>);
	ASSERT_PARSER_VALUES_EQ(exa4, (l1 >> oc1) % exactly<2>);
}



constexpr auto exactly_checker = []<Parser P>(P) -> bool
{
	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { exactly<2>(P{}); },  "exactly<2> prefix operator compiles, but it shouldn't" );
		TOK3N_ASSERT_P( not requires { P{} % exactly<2>; }, "exactly<2> infix operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { exactly<2>(P{}); },         "exactly<2> prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( exactly<2>(P{}) == (Exactly<P, 2>{}),  "exactly<2> prefix operator of any other parser should give Exactly parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % exactly<2>; },        "exactly<2> infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % exactly<2> == (Exactly<P, 2>{}), "exactly<2> infix operator of any other parser should give Exactly parser of the argument" );
	}

	return true;
};

TEST("exactly modifier", "modify anything")
{
	assert
		, check_all_samples(exactly_checker)
		;
}
