#include "pch.h"

TEST("zero_or_more operator", "*Maybe")
{
	ASSERT_PARSER_VALUES_EQ(*may1, zom1);
	ASSERT_PARSER_VALUES_EQ(**may1, zom1);
	ASSERT_PARSER_VALUES_EQ(***may1, zom1);
	ASSERT_PARSER_VALUES_EQ(*may2, zom2);
	ASSERT_PARSER_VALUES_EQ(**may2, zom2);
	ASSERT_PARSER_VALUES_EQ(***may2, zom2);
	ASSERT_PARSER_VALUES_EQ(*may3, zom3);
	ASSERT_PARSER_VALUES_EQ(**may3, zom3);
	ASSERT_PARSER_VALUES_EQ(***may3, zom3);
	ASSERT_PARSER_VALUES_EQ(*may4, zom4);
	ASSERT_PARSER_VALUES_EQ(**may4, zom4);
	ASSERT_PARSER_VALUES_EQ(***may4, zom4);
}

TEST("zero_or_more operator", "*OneOrMore")
{
	ASSERT_PARSER_VALUES_EQ(*oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(**oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(***oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(*oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(**oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(***oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(*oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(**oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(***oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(*oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(**oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(***oom4, zom4);
}

TEST("zero_or_more operator", "*ZeroOrMore")
{
	ASSERT_PARSER_VALUES_EQ(*zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(**zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(***zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(*zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(**zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(***zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(*zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(**zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(***zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(*zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(**zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(***zom4, zom4);
}



constexpr auto zero_or_more_checker = []<Parser P>(P) -> bool
{
	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { *P{}; }, "zero_or_more operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { *P{}; },               "zero_or_more operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( requires { { *P{} } -> Parser; }, "zero_or_more operator compiles, but doesn't give a Parser" );

		if constexpr (P::type == MaybeType)
			TOK3N_ASSERT_P( *P{} == ZeroOrMore<underlying::parser<P>>{}, "zero_or_more operator of Maybe parser should give ZeroOrMore parser of the underlying" );

		else if constexpr (P::type == OneOrMoreType)
			TOK3N_ASSERT_P( *P{} == ZeroOrMore<underlying::parser<P>>{}, "zero_or_more operator of OneOrMore parser should give ZeroOrMore parser of the underlying" );

		else if constexpr (P::type == ZeroOrMoreType)
			TOK3N_ASSERT_P( *P{} == P{}, "zero_or_more operator of ZeroOrMore parser should give itself" );

		else
			TOK3N_ASSERT_P( *P{} == ZeroOrMore<P>{}, "zero_or_more operator of any other parser should give ZeroOrMore parser of the argument" );
	}

	return true;
};

TEST("zero_or_more operator", "*{anything}")
{
	assert
		, check_all_samples(zero_or_more_checker)
		;
}
