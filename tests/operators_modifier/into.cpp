#include "pch.h"

TOK3N_BEGIN_NAMESPACE(tests)

inline void prefix()
{
	assert
		, int1 == into<Class1>(spacedot)
		, int2 == into<Class2>(abc >> spacedot)
		;
}

inline void infix()
{
	assert
		, int1 == spacedot % into<Class1>
		, int2 == (abc >> spacedot) % into<Class2>
		;
}



constexpr auto into_checker = []<Parser P>(P) -> bool
{
	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { into<Sink>(P{}); },  "into<Sink> prefix operator compiles, but it shouldn't" );
		TOK3N_ASSERT_P( not requires { P{} % into<Sink>; }, "into<Sink> infix operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { into<Sink>(P{}); },         "into<Sink> prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( into<Sink>(P{}) == (Into<P, Sink>{}),  "into<Sink> prefix operator of any other parser should give Into parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % into<Sink>; },        "into<Sink> infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % into<Sink> == (Into<P, Sink>{}), "into<Sink> infix operator of any other parser should give Into parser of the argument" );
	}

	return true;
};

inline void into_anything()
{
	assert
		, check_all_samples(into_checker)
		;
}

TOK3N_END_NAMESPACE(tests)