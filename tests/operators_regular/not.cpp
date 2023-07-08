#include "pch.h"

TEST("not operator", "!OneChar")
{
	ASSERT_PARSER_VALUES_EQ(!oc1, nc1);
	ASSERT_PARSER_VALUES_EQ(!oc2, nc2);
	ASSERT_PARSER_VALUES_EQ(!oc3, nc3);
	ASSERT_PARSER_VALUES_EQ(!!oc1, oc1);
	ASSERT_PARSER_VALUES_EQ(!!oc2, oc2);
	ASSERT_PARSER_VALUES_EQ(!!oc3, oc3);
}

TEST("not operator", "!NotChar")
{
	ASSERT_PARSER_VALUES_EQ(!nc1, oc1);
	ASSERT_PARSER_VALUES_EQ(!nc2, oc2);
	ASSERT_PARSER_VALUES_EQ(!nc3, oc3);
	ASSERT_PARSER_VALUES_EQ(!!nc1, nc1);
	ASSERT_PARSER_VALUES_EQ(!!nc2, nc2);
	ASSERT_PARSER_VALUES_EQ(!!nc3, nc3);
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

TEST("not operator", "!{anything}")
{
	ASSERT(check_all_samples(not_checker), "check_all_samples(not_checker) failed");
}
