#include "pch.h"

inline void not_OneChar()
{
	assert
		, !oc1 == nc1
		, !oc2 == nc2
		, !oc3 == nc3
		, !!oc1 == oc1
		, !!oc2 == oc2
		, !!oc3 == oc3
		;
}

inline void not_NotChar()
{
	assert
		, !nc1 == oc1
		, !nc2 == oc2
		, !nc3 == oc3
		, !!nc1 == nc1
		, !!nc2 == nc2
		, !!nc3 == nc3
		;
}



constexpr auto not_checker = []<Parser P>(P) -> bool
{
	if constexpr (P::type == OneCharType)
	{
		TOK3N_ASSERT_P( requires { !P{}; },                       "not operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( (!P{}).type == NotCharType,               "not operator of OneChar parser should give NotChar parser" );
		TOK3N_ASSERT_P( !P{} == NotChar<underlying::string<P>>{}, "not operator of OneChar parser should give NotChar parser of the underlying string" );
	}
	else if constexpr (P::type == NotCharType)
	{
		TOK3N_ASSERT_P( requires { !P{}; },                       "not operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( (!P{}).type == OneCharType,               "not operator of NotChar parser should give OneChar parser" );
		TOK3N_ASSERT_P( !P{} == OneChar<underlying::string<P>>{}, "not operator of NotChar parser should give OneChar parser of the underlying string" );
	}
	else
	{
		TOK3N_ASSERT_P( not requires { !P{}; }, "not operator compiles, but it shouldn't" );
	}

	return true;
};

inline void not_anything()
{
	assert
		, check_all_samples(not_checker)
		;
}
