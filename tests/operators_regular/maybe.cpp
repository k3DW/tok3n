#include "pch.h"

TEST("maybe operator", "~Maybe")
{
	assert
		, ~may1 == may1
		, ~~may1 == may1
		, ~~~may1 == may1
		, ~may2 == may2
		, ~~may2 == may2
		, ~~~may2 == may2
		, ~may3 == may3
		, ~~may3 == may3
		, ~~~may3 == may3
		, ~may4 == may4
		, ~~may4 == may4
		, ~~~may4 == may4
		;
}

TEST("maybe operator", "~OneOrMore")
{
	assert
		, ~oom1 == zom1
		, ~~oom1 == zom1
		, ~~~oom1 == zom1
		, ~oom2 == zom2
		, ~~oom2 == zom2
		, ~~~oom2 == zom2
		, ~oom3 == zom3
		, ~~oom3 == zom3
		, ~~~oom3 == zom3
		, ~oom4 == zom4
		, ~~oom4 == zom4
		, ~~~oom4 == zom4
		;
}

TEST("maybe operator", "~ZeroOrMore")
{
	assert
		, ~zom1 == zom1
		, ~~zom1 == zom1
		, ~~~zom1 == zom1
		, ~zom2 == zom2
		, ~~zom2 == zom2
		, ~~~zom2 == zom2
		, ~zom3 == zom3
		, ~~zom3 == zom3
		, ~~~zom3 == zom3
		, ~zom4 == zom4
		, ~~zom4 == zom4
		, ~~~zom4 == zom4
		;
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
	assert
		, check_all_samples(maybe_checker)
		;
}
