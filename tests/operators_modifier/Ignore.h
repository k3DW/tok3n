#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Ignore)

using namespace samples::all;

void ignore_operator()
{
	assert
		, ign1 == ignore(abc)
		, ign2 == ignore(+abc)
		, ign3 == ignore(~(abc | qq))
		, ign4 == ignore(abc >> *qq)
		, ign5 == ignore(+abc >> ~(abc | qq))

		, ign1 == ignore(ign1)
		, ign2 == ignore(ign2)
		, ign3 == ignore(ign3)
		, ign4 == ignore(ign4)
		, ign5 == ignore(ign5)
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::Ignore)
