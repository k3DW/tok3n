#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Defaulted)

using namespace samples::all;

void prefix()
{
	assert
		, def1 == defaulted<int>(+abc)
		, def2 == defaulted<Class3>(~(abc | qq))
		;
}

void infix()
{
	assert
		, def1 == +abc % defaulted<int>
		, def2 == ~(abc | qq) % defaulted<Class3>
		;
}



void defaulted_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(modifier::Defaulted)
