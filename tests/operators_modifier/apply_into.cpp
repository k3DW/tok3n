#include "pch.h"

FIXTURE("apply_into modifier");

TEST("apply_into modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(api1, apply_into<Class2>(abc >> spacedot));
	ASSERT_PARSER_VALUES_EQ(api2, apply_into<Class5>(spacedot >> abc));
}

TEST("apply_into modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(api1, (abc >> spacedot) % apply_into<Class2>);
	ASSERT_PARSER_VALUES_EQ(api2, (spacedot >> abc) % apply_into<Class5>);
}



constexpr auto apply_into_checker = []<Parser P>(P) -> bool
{
	if constexpr (detail::has_tuple_size<typename P::result_type>)
	{
		TOK3N_ASSERT_P( requires { apply_into<Sink>(P{}); },              "apply_into<Sink> prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( apply_into<Sink>(P{}) == (ApplyInto<P, Sink>{}),  "apply_into<Sink> prefix operator of any other parser should give ApplyInto parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % apply_into<Sink>; },             "apply_into<Sink> infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % apply_into<Sink> == (ApplyInto<P, Sink>{}), "apply_into<Sink> infix operator of any other parser should give ApplyInto parser of the argument" );
	}
	else
	{
		TOK3N_ASSERT_P( not requires { apply_into<Sink>(P{}); },  "apply_into<Sink> prefix operator compiles, but it shouldn't" );
		TOK3N_ASSERT_P( not requires { P{} % apply_into<Sink>; }, "apply_into<Sink> infix operator compiles, but it shouldn't" );
	}

	return true;
};

TEST("apply_into modifier", "modify anything")
{
	ASSERT(check_all_samples(apply_into_checker), "check_all_samples(apply_into_checker) failed");
}
