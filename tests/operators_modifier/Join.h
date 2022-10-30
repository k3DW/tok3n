#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Join)

using namespace samples::all;

void join_prefix()
{
	assert
		, joi1 != join(abc)
		, abc == join(abc)
		, joi2 == join(+abc)
		, joi3 == join(~(abc | qq))
		, joi4 == join(abc >> *qq)
		, joi5 == join(+abc >> ~(abc | qq))
		, joi1 == join(joi1)
		, joi2 == join(joi2)
		, joi3 == join(joi3)
		, joi4 == join(joi4)
		, joi5 == join(joi5)
		;
}

void join_infix()
{
	assert
		, joi1 != abc % join
		, abc == abc % join
		, joi2 == +abc % join
		, joi3 == ~(abc | qq) % join
		, joi4 == (abc >> *qq) % join
		, joi5 == (+abc >> ~(abc | qq)) % join
		, joi1 == joi1 % join
		, joi2 == joi2 % join
		, joi3 == joi3 % join
		, joi4 == joi4 % join
		, joi5 == joi5 % join
		;
}



void join_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(modifier::Join)
