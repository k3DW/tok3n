#include "pch.h"

TEST("delimit_keep modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(dek1, delimit_keep(abc, comma));
	ASSERT_PARSER_VALUES_EQ(dek2, delimit_keep(abc, spacedot));
	ASSERT_PARSER_VALUES_EQ(dek3, delimit_keep(qq, comma));
	ASSERT_PARSER_VALUES_EQ(dek4, delimit_keep(qq, spacedot));
	ASSERT_PARSER_VALUES_EQ(dek5, delimit_keep(comma, abc));
	ASSERT_PARSER_VALUES_EQ(dek6, delimit_keep(spacedot, abc));
	ASSERT_PARSER_VALUES_EQ(dek7, delimit_keep(comma, qq));
	ASSERT_PARSER_VALUES_EQ(dek8, delimit_keep(spacedot, qq));
}

TEST("delimit_keep modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(dek1, abc % delimit_keep(comma));
	ASSERT_PARSER_VALUES_EQ(dek2, abc % delimit_keep(spacedot));
	ASSERT_PARSER_VALUES_EQ(dek3, qq % delimit_keep(comma));
	ASSERT_PARSER_VALUES_EQ(dek4, qq % delimit_keep(spacedot));
	ASSERT_PARSER_VALUES_EQ(dek5, comma % delimit_keep(abc));
	ASSERT_PARSER_VALUES_EQ(dek6, spacedot % delimit_keep(abc));
	ASSERT_PARSER_VALUES_EQ(dek7, comma % delimit_keep(qq));
	ASSERT_PARSER_VALUES_EQ(dek8, spacedot % delimit_keep(qq));
}



constexpr auto delimit_keep_checker = []<Parser P>(P) -> bool
{
	TOK3N_ASSERT_P( not requires { delimit_keep(P{}, ignore(comma)); },  "delimit_keep prefix operator compiles with an ignored delimiter, but it shouldn't" );
	TOK3N_ASSERT_P( not requires { P{} % delimit_keep(ignore(comma)); }, "delimit_keep infix operator compiles with an ignored delimiter, but it shouldn't" );

	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { delimit_keep(P{}, comma); },  "delimit_keep prefix operator compiles, but it shouldn't" );
		TOK3N_ASSERT_P( not requires { P{} % delimit_keep(comma); }, "delimit_keep infix operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { delimit_keep(P{}, comma); },                             "delimit_keep prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( delimit_keep(P{}, comma) == (Delimit<P, Comma, std::true_type>{}),  "delimit_keep prefix operator of any other parser should give Delimit parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % delimit_keep(comma); },                            "delimit_keep infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % delimit_keep(comma) == (Delimit<P, Comma, std::true_type>{}), "delimit_keep infix operator of any other parser should give Delimit parser of the argument" );
	}

	return true;
};

TEST("delimit_keep modifier", "modify anything")
{
	assert
		, check_all_samples(delimit_keep_checker)
		;
}
