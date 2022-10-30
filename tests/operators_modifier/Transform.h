#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Transform)

using namespace samples::all;

void transform_prefix()
{
	assert
		, tra1 == fn<func1>(+abc)
		, tra2 == fn<func2>(~(abc | qq))
		, tra3 == fn<func3>(abc >> *qq)
		, tra4 == fn<func4(3)>(+abc >> ~(abc | qq))
		, tra4 != fn<func4(2)>(+abc >> ~(abc | qq))
		;
}

void transform_infix()
{
	assert
		, tra1 == +abc % fn<func1>
		, tra2 == ~(abc | qq) % fn<func2>
		, tra3 == (abc >> *qq) % fn<func3>
		, tra4 == (+abc >> ~(abc | qq)) % fn<func4(3)>
		, tra4 != (+abc >> ~(abc | qq)) % fn<func4(2)>
		;
}



void transform_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(modifier::Transform)
