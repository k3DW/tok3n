#include "pch.h"

static void prefix()
{
	assert
		, com1 == complete(l1)
		, com2 == complete(oc1)
		, com3 == complete(l1 | oc1)
		, com4 == complete(l1 >> oc1)
		, com5 == complete(~(l1 >> oc1))
		, com6 == complete(+(l1 >> oc1))
		, com7 == complete(*(l1 >> oc1))
		;
}

static void infix()
{
	assert
		, com1 == l1 % complete
		, com2 == oc1 % complete
		, com3 == (l1 | oc1) % complete
		, com4 == (l1 >> oc1) % complete
		, com5 == ~(l1 >> oc1) % complete
		, com6 == +(l1 >> oc1) % complete
		, com7 == *(l1 >> oc1) % complete
		;
}

static void idempotent()
{
	assert
		, com1 == complete(com1)
		, com2 == complete(com2)
		, com3 == complete(com3)
		, com4 == complete(com4)
		, com5 == complete(com5)
		, com6 == complete(com6)
		, com7 == complete(com7)
		, com1 == com1 % complete
		, com2 == com2 % complete
		, com3 == com3 % complete
		, com4 == com4 % complete
		, com5 == com5 % complete
		, com6 == com6 % complete
		, com7 == com7 % complete
		;
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

static void complete_anything()
{
	assert
		, check_all_samples(complete_checker)
		;
}

void complete_tests()
{
	prefix();
	infix();
	idempotent();
	complete_anything();
}
