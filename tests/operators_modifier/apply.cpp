#include "pch.h"

TEST("apply modifier", "prefix")
{
	assert
		, apt1 == apply<func3_apply>(abc >> *qq)
		, apt2 == apply<func4_apply(3)>(+abc >> ~(abc | qq))
		, apt2 != apply<func4_apply(2)>(+abc >> ~(abc | qq))
		;
}

TEST("apply modifier", "infix")
{
	assert
		, apt1 == (abc >> *qq) % apply<func3_apply>
		, apt2 == (+abc >> ~(abc | qq)) % apply<func4_apply(3)>
		, apt2 != (+abc >> ~(abc | qq)) % apply<func4_apply(2)>
		;
}



constexpr auto apply_checker = []<Parser P>(P) -> bool
{
	if constexpr (detail::has_tuple_size<typename P::result_type>)
	{
		TOK3N_ASSERT_P( requires { apply<sink_func>(P{}); },                       "apply<sink_func> prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( apply<sink_func>(P{}) == (ApplyTransform<P, sink_func>{}),  "apply<sink_func> prefix operator of any other parser should give ApplyTransform parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % apply<sink_func>; },                      "apply<sink_func> infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % apply<sink_func> == (ApplyTransform<P, sink_func>{}), "apply<sink_func> infix operator of any other parser should give ApplyTransform parser of the argument" );
	}
	else
	{
		TOK3N_ASSERT_P( not requires { apply<sink_func>(P{}); },  "apply<sink_func> prefix operator compiles, but it shouldn't" );
		TOK3N_ASSERT_P( not requires { P{} % apply<sink_func>; }, "apply<sink_func> infix operator compiles, but it shouldn't" );
	}

	return true;
};

TEST("apply modifier", "modify anything")
{
	assert
		, check_all_samples(apply_checker)
		;
}
