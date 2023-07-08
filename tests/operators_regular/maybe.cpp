#include "pch.h"

TEST("maybe operator", "~Maybe")
{
	ASSERT_PARSER_VALUES_EQ(~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~~~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~~~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~~~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~may4, may4);
	ASSERT_PARSER_VALUES_EQ(~~may4, may4);
	ASSERT_PARSER_VALUES_EQ(~~~may4, may4);
}

TEST("maybe operator", "~OneOrMore")
{
	ASSERT_PARSER_VALUES_EQ(~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~~oom4, zom4);
}

TEST("maybe operator", "~ZeroOrMore")
{
	ASSERT_PARSER_VALUES_EQ(~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~~zom4, zom4);
}



constexpr auto maybe_checker = []<Parser P>(P) -> bool
{
	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { ~P{}; }, "maybe operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { ~P{}; },               "maybe operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( requires { { ~P{} } -> Parser; }, "maybe operator compiles, but doesn't give a Parser" );

		if constexpr (P::type == MaybeType)
			TOK3N_ASSERT_P( ~P{} == P{}, "maybe operator of Maybe parser should give itself" );

		else if constexpr (P::type == OneOrMoreType)
			TOK3N_ASSERT_P( ~P{} == ZeroOrMore<underlying::parser<P>>{}, "maybe operator of OneOrMore parser should give ZeroOrMore parser of the underlying" );

		else if constexpr (P::type == ZeroOrMoreType)
			TOK3N_ASSERT_P( ~P{} == P{}, "maybe operator of ZeroOrMore parser should give itself" );

		else
			TOK3N_ASSERT_P( ~P{} == Maybe<P>{}, "maybe operator of any other parser should give Maybe parser of the argument" );
	}

	return true;
};

TEST("maybe operator", "~{anything}")
{
	ASSERT(check_all_samples(maybe_checker), "check_all_samples(maybe_checker) failed");
}
