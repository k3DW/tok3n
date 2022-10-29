#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(regular::Maybe)

using namespace samples::all;

void Maybe_Maybe()
{
	assert
		, ~may1 == may1
		, ~~may1 == may1
		, ~~~may1 == may1
		, ~may2 == may2
		, ~~may2 == may2
		, ~~~may2 == may2
		, ~may3 == may3
		, ~~may3 == may3
		, ~~~may3 == may3
		, ~may4 == may4
		, ~~may4 == may4
		, ~~~may4 == may4
		;
}

void Maybe_OneOrMore()
{
	assert
		, ~oom1 == zom1
		, ~~oom1 == zom1
		, ~~~oom1 == zom1
		, ~oom2 == zom2
		, ~~oom2 == zom2
		, ~~~oom2 == zom2
		, ~oom3 == zom3
		, ~~oom3 == zom3
		, ~~~oom3 == zom3
		, ~oom4 == zom4
		, ~~oom4 == zom4
		, ~~~oom4 == zom4
		;
}

void Maybe_ZeroOrMore()
{
	assert
		, ~zom1 == zom1
		, ~~zom1 == zom1
		, ~~~zom1 == zom1
		, ~zom2 == zom2
		, ~~zom2 == zom2
		, ~~~zom2 == zom2
		, ~zom3 == zom3
		, ~~zom3 == zom3
		, ~~~zom3 == zom3
		, ~zom4 == zom4
		, ~~zom4 == zom4
		, ~~~zom4 == zom4
		;
}



void Maybe_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(regular::Maybe)
