#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(regular::ZeroOrMore)

using namespace samples::all;

void ZeroOrMore_Maybe()
{
	assert
		, *may1 == zom1
		, **may1 == zom1
		, ***may1 == zom1
		, *may2 == zom2
		, **may2 == zom2
		, ***may2 == zom2
		, *may3 == zom3
		, **may3 == zom3
		, ***may3 == zom3
		, *may4 == zom4
		, **may4 == zom4
		, ***may4 == zom4
		;
}

void ZeroOrMore_OneOrMore()
{
	assert
		, *oom1 == zom1
		, **oom1 == zom1
		, ***oom1 == zom1
		, *oom2 == zom2
		, **oom2 == zom2
		, ***oom2 == zom2
		, *oom3 == zom3
		, **oom3 == zom3
		, ***oom3 == zom3
		, *oom4 == zom4
		, **oom4 == zom4
		, ***oom4 == zom4
		;
}

void ZeroOrMore_ZeroOrMore()
{
	assert
		, *zom1 == zom1
		, **zom1 == zom1
		, ***zom1 == zom1
		, *zom2 == zom2
		, **zom2 == zom2
		, ***zom2 == zom2
		, *zom3 == zom3
		, **zom3 == zom3
		, ***zom3 == zom3
		, *zom4 == zom4
		, **zom4 == zom4
		, ***zom4 == zom4
		;
}



void ZeroOrMore_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(regular::ZeroOrMore)
