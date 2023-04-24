#include "pch.h"

TOK3N_BEGIN_NAMESPACE(tests)

inline void prefix()
{
	assert
		, tra1 == fn<func1>(+abc)
		, tra2 == fn<func2>(~(abc | qq))
		, tra3 == fn<func3>(abc >> *qq)
		, tra4 == fn<func4(3)>(+abc >> ~(abc | qq))
		, tra4 != fn<func4(2)>(+abc >> ~(abc | qq))
		;
}

inline void infix()
{
	assert
		, tra1 == +abc % fn<func1>
		, tra2 == ~(abc | qq) % fn<func2>
		, tra3 == (abc >> *qq) % fn<func3>
		, tra4 == (+abc >> ~(abc | qq)) % fn<func4(3)>
		, tra4 != (+abc >> ~(abc | qq)) % fn<func4(2)>
		;
}



constexpr auto fn_checker = []<Parser P>(P) -> bool
{
	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { fn<sink_func>(P{}); },  "fn<sink_func> prefix operator compiles, but it shouldn't" );
		TOK3N_ASSERT_P( not requires { P{} % fn<sink_func>; }, "fn<sink_func> infix operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { fn<sink_func>(P{}); },                   "fn<sink_func> prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( fn<sink_func>(P{}) == (Transform<P, sink_func>{}),  "fn<sink_func> prefix operator of any other parser should give Transform parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % fn<sink_func>; },                  "fn<sink_func> infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % fn<sink_func> == (Transform<P, sink_func>{}), "fn<sink_func> infix operator of any other parser should give Transform parser of the argument" );
	}

	return true;
};

inline void fn_anything()
{
	assert
		, check_all_samples(fn_checker)
		;
}

TOK3N_END_NAMESPACE(tests)
