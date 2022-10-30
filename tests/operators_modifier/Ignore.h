#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Ignore)

using namespace samples::all;

void prefix()
{
	assert
		, ign1 == ignore(abc)
		, ign2 == ignore(+abc)
		, ign3 == ignore(~(abc | qq))
		, ign4 == ignore(abc >> *qq)
		, ign5 == ignore(+abc >> ~(abc | qq))
		;
}

void infix()
{
	assert
		, ign1 == abc % ignore
		, ign2 == +abc % ignore
		, ign3 == ~(abc | qq) % ignore
		, ign4 == (abc >> *qq) % ignore
		, ign5 == (+abc >> ~(abc | qq)) % ignore
		;
}

void idempotent()
{
	assert
		, ign1 == ignore(ign1)
		, ign2 == ignore(ign2)
		, ign3 == ignore(ign3)
		, ign4 == ignore(ign4)
		, ign5 == ignore(ign5)
		, ign1 == ign1 % ignore
		, ign2 == ign2 % ignore
		, ign3 == ign3 % ignore
		, ign4 == ign4 % ignore
		, ign5 == ign5 % ignore
		;
}



void ignore_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(modifier::Ignore)
