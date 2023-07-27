#include "pch.h"

FIXTURE("delimit modifier");

TEST("delimit modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(del1, delimit(abc, comma));
	ASSERT_PARSER_VALUES_EQ(del2, delimit(abc, spacedot));
	ASSERT_PARSER_VALUES_EQ(del3, delimit(qq, comma));
	ASSERT_PARSER_VALUES_EQ(del4, delimit(qq, spacedot));
	ASSERT_PARSER_VALUES_EQ(del5, delimit(comma, abc));
	ASSERT_PARSER_VALUES_EQ(del6, delimit(spacedot, abc));
	ASSERT_PARSER_VALUES_EQ(del7, delimit(comma, qq));
	ASSERT_PARSER_VALUES_EQ(del8, delimit(spacedot, qq));
}

TEST("delimit modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(del1, abc % delimit(comma));
	ASSERT_PARSER_VALUES_EQ(del2, abc % delimit(spacedot));
	ASSERT_PARSER_VALUES_EQ(del3, qq % delimit(comma));
	ASSERT_PARSER_VALUES_EQ(del4, qq % delimit(spacedot));
	ASSERT_PARSER_VALUES_EQ(del5, comma % delimit(abc));
	ASSERT_PARSER_VALUES_EQ(del6, spacedot % delimit(abc));
	ASSERT_PARSER_VALUES_EQ(del7, comma % delimit(qq));
	ASSERT_PARSER_VALUES_EQ(del8, spacedot % delimit(qq));
}



constexpr auto delimit_checker = []<Parser P>(P) -> bool
{
	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { delimit(P{}, comma); },  "delimit prefix operator compiles, but it shouldn't" );
		TOK3N_ASSERT_P( not requires { P{} % delimit(comma); }, "delimit infix operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { delimit(P{}, comma); },                    "delimit prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( delimit(P{}, comma) == (Delimit<P, Comma, False>{}),  "delimit prefix operator of any other parser should give Delimit parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % delimit(comma); },                   "delimit infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % delimit(comma) == (Delimit<P, Comma, False>{}), "delimit infix operator of any other parser should give Delimit parser of the argument" );
	}

	return true;
};

TEST("delimit modifier", "modify anything")
{
	ASSERT(check_all_samples(delimit_checker), "check_all_samples(delimit_checker) failed");
}
