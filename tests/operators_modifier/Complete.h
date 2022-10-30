#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Complete)

using namespace samples::all;

void prefix()
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

void infix()
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

void idempotent()
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



void complete_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(modifier::Complete)
