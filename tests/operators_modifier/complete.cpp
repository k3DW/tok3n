#include "pch.h"

FIXTURE("complete modifier");

TEST("complete modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(com1, complete(l1));
	ASSERT_PARSER_VALUES_EQ(com2, complete(oc1));
	ASSERT_PARSER_VALUES_EQ(com3, complete(l1 | oc1));
	ASSERT_PARSER_VALUES_EQ(com4, complete(l1 >> oc1));
	ASSERT_PARSER_VALUES_EQ(com5, complete(~(l1 >> oc1)));
	ASSERT_PARSER_VALUES_EQ(com6, complete(+(l1 >> oc1)));
	ASSERT_PARSER_VALUES_EQ(com7, complete(*(l1 >> oc1)));
}

TEST("complete modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(com1, l1 % complete);
	ASSERT_PARSER_VALUES_EQ(com2, oc1 % complete);
	ASSERT_PARSER_VALUES_EQ(com3, (l1 | oc1) % complete);
	ASSERT_PARSER_VALUES_EQ(com4, (l1 >> oc1) % complete);
	ASSERT_PARSER_VALUES_EQ(com5, ~(l1 >> oc1) % complete);
	ASSERT_PARSER_VALUES_EQ(com6, +(l1 >> oc1) % complete);
	ASSERT_PARSER_VALUES_EQ(com7, *(l1 >> oc1) % complete);
}

TEST("complete modifier", "idempotent")
{
	ASSERT_PARSER_VALUES_EQ(com1, complete(com1));
	ASSERT_PARSER_VALUES_EQ(com2, complete(com2));
	ASSERT_PARSER_VALUES_EQ(com3, complete(com3));
	ASSERT_PARSER_VALUES_EQ(com4, complete(com4));
	ASSERT_PARSER_VALUES_EQ(com5, complete(com5));
	ASSERT_PARSER_VALUES_EQ(com6, complete(com6));
	ASSERT_PARSER_VALUES_EQ(com7, complete(com7));
	ASSERT_PARSER_VALUES_EQ(com1, com1 % complete);
	ASSERT_PARSER_VALUES_EQ(com2, com2 % complete);
	ASSERT_PARSER_VALUES_EQ(com3, com3 % complete);
	ASSERT_PARSER_VALUES_EQ(com4, com4 % complete);
	ASSERT_PARSER_VALUES_EQ(com5, com5 % complete);
	ASSERT_PARSER_VALUES_EQ(com6, com6 % complete);
	ASSERT_PARSER_VALUES_EQ(com7, com7 % complete);
}



constexpr auto complete_checker = []<Parser P>(P) -> bool
{
	if constexpr (P::type == CompleteType)
	{
		TOK3N_ASSERT_P( requires { complete(P{}); },  "complete prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( complete(P{}) == P{},         "complete prefix operator of Complete parser should give itself" );
		TOK3N_ASSERT_P( requires { P{} % complete; }, "complete infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % complete == P{},        "complete infix operator of Complete parser should give itself" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { complete(P{}); },     "complete prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( complete(P{}) == Complete<P>{},  "complete prefix operator of any other parser should give Complete parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % complete; },    "complete infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % complete == Complete<P>{}, "complete infix operator of any other parser should give Complete parser of the argument" );
	}

	return true;
};

TEST("complete modifier", "modify anything")
{
	ASSERT(check_all_samples(complete_checker), "check_all_samples(complete_checker) failed");
}
