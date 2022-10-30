#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Exactly)

using namespace samples::all;

void prefix()
{
	assert
		, exa1 == exactly<3>(l1)
		, exa2 == exactly<5>(oc1)
		, exa3 == exactly<4>(l1 | oc1)
		, exa4 == exactly<2>(l1 >> oc1)
		;
}

void infix()
{
	assert
		, exa1 == l1 % exactly<3>
		, exa2 == oc1 % exactly<5>
		, exa3 == (l1 | oc1) % exactly<4>
		, exa4 == (l1 >> oc1) % exactly<2>
		;
}



void exactly_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(modifier::Exactly)
