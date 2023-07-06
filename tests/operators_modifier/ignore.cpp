#include "pch.h"

TEST("ignore modifier", "prefix")
{
	assert
		, ign1 == ignore(abc)
		, ign2 == ignore(+abc)
		, ign3 == ignore(~(abc | qq))
		, ign4 == ignore(abc >> *qq)
		, ign5 == ignore(+abc >> ~(abc | qq))
		;
}

TEST("ignore modifier", "infix")
{
	assert
		, ign1 == abc % ignore
		, ign2 == +abc % ignore
		, ign3 == ~(abc | qq) % ignore
		, ign4 == (abc >> *qq) % ignore
		, ign5 == (+abc >> ~(abc | qq)) % ignore
		;
}

TEST("ignore modifier", "idempotent")
{
	assert
		, ign1 == ignore(ign1)
		, ign2 == ignore(ign2)
		, ign3 == ignore(ign3)
		, ign4 == ignore(ign4)
		, ign5 == ignore(ign5)
		, ign1 == ign1 % ignore
		, ign2 == ign2 % ignore
		, ign3 == ign3 % ignore
		, ign4 == ign4 % ignore
		, ign5 == ign5 % ignore
		;
}



constexpr auto ignore_checker = []<Parser P>(P) -> bool
{
	if constexpr (P::type == IgnoreType)
	{
		TOK3N_ASSERT_P( requires { ignore(P{}); },  "ignore prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( ignore(P{}) == P{},         "ignore prefix operator of Ignore parser should give itself" );
		TOK3N_ASSERT_P( requires { P{} % ignore; }, "ignore infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % ignore == P{},        "ignore infix operator of Ignore parser should give itself" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { ignore(P{}); },   "ignore prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( ignore(P{}) == Ignore<P>{},  "ignore prefix operator of any other parser should give Ignore parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % ignore; },  "ignore infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % ignore == Ignore<P>{}, "ignore infix operator of any other parser should give Ignore parser of the argument" );
	}

	return true;
};

TEST("ignore modifier", "modify anything")
{
	assert
		, check_all_samples(ignore_checker)
		;
}
