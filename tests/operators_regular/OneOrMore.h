#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(regular::OneOrMore)

using namespace samples::all;

void OneOrMore_Maybe()
{
	assert
		, +may1 == zom1
		, + +may1 == zom1
		, + + +may1 == zom1
		, +may2 == zom2
		, + +may2 == zom2
		, + + +may2 == zom2
		, +may3 == zom3
		, + +may3 == zom3
		, + + +may3 == zom3
		, +may4 == zom4
		, + +may4 == zom4
		, + + +may4 == zom4
		;
}

void OneOrMore_OneOrMore()
{
	assert
		, +oom1 == oom1
		, + +oom1 == oom1
		, + + +oom1 == oom1
		, +oom2 == oom2
		, + +oom2 == oom2
		, + + +oom2 == oom2
		, +oom3 == oom3
		, + +oom3 == oom3
		, + + +oom3 == oom3
		, +oom4 == oom4
		, + +oom4 == oom4
		, + + +oom4 == oom4
		;
}

void OneOrMore_ZeroOrMore()
{
	assert
		, +zom1 == zom1
		, + +zom1 == zom1
		, + + +zom1 == zom1
		, +zom2 == zom2
		, + +zom2 == zom2
		, + + +zom2 == zom2
		, +zom3 == zom3
		, + +zom3 == zom3
		, + + +zom3 == zom3
		, +zom4 == zom4
		, + +zom4 == zom4
		, + + +zom4 == zom4
		;
}



void OneOrMore_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(regular::OneOrMore)
