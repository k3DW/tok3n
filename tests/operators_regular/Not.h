#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(operators::Not)

using namespace samples::basic;

void not_OneChar()
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

void not_NotChar()
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

TOK3N_END_NAMESPACE_TESTS(operators::Not)
