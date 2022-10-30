#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Delimit)

using namespace samples::all;

void delimit_operator()
{
	assert
		, del1 == delimit(abc, comma)
		, del2 == delimit(abc, spacedot)
		, del3 == delimit(qq, comma)
		, del4 == delimit(qq, spacedot)
		, del5 == delimit(comma, abc)
		, del6 == delimit(spacedot, abc)
		, del7 == delimit(comma, qq)
		, del8 == delimit(spacedot, qq)
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::Delimit)
