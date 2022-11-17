#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Constant)

using namespace samples::all;

void prefix()
{
	assert
		, con1 == constant<1>(+abc)
		, con2 == constant<'t'>(~(abc | qq))
		, con3 == constant<true>(abc >> *qq)
		, con4 == constant<nullptr>(+abc >> ~(abc | qq))
		;
}

void infix()
{
	assert
		, con1 == +abc % constant<1>
		, con2 == ~(abc | qq) % constant<'t'>
		, con3 == (abc >> *qq) % constant<true>
		, con4 == (+abc >> ~(abc | qq)) % constant<nullptr>
		;
}



void constant_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(modifier::Constant)
