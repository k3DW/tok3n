#include "pch.h"

TOK3N_BEGIN_NAMESPACE(tests)

inline void prefix()
{
	assert
		, con1 == constant<1>(+abc)
		, con2 == constant<'t'>(~(abc | qq))
		, con3 == constant<true>(abc >> *qq)
		, con4 == constant<nullptr>(+abc >> ~(abc | qq))
		;
}

inline void infix()
{
	assert
		, con1 == +abc % constant<1>
		, con2 == ~(abc | qq) % constant<'t'>
		, con3 == (abc >> *qq) % constant<true>
		, con4 == (+abc >> ~(abc | qq)) % constant<nullptr>
		;
}



constexpr auto constant_checker = []<Parser P>(P) -> bool
{
	TOK3N_ASSERT_P( requires { constant<0>(P{}); },          "constant<0> prefix operator doesn't compile, but it should" );
	TOK3N_ASSERT_P( constant<0>(P{}) == (Constant<P, 0>{}),  "constant<0> prefix operator of any other parser should give Constant parser of the argument" );
	TOK3N_ASSERT_P( requires { P{} % constant<0>; },         "constant<0> infix operator doesn't compile, but it should" );
	TOK3N_ASSERT_P( P{} % constant<0> == (Constant<P, 0>{}), "constant<0> infix operator of any other parser should give Constant parser of the argument" );

	return true;
};

inline void constant_anything()
{
	assert
		, check_all_samples(constant_checker)
		;
}

TOK3N_END_NAMESPACE(tests)
