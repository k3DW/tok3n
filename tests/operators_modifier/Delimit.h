#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Delimit)

using namespace samples::all;

void prefix()
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

void infix()
{
	assert
		, del1 == abc % delimit(comma)
		, del2 == abc % delimit(spacedot)
		, del3 == qq % delimit(comma)
		, del4 == qq % delimit(spacedot)
		, del5 == comma % delimit(abc)
		, del6 == spacedot % delimit(abc)
		, del7 == comma % delimit(qq)
		, del8 == spacedot % delimit(qq)
		;
}



void delimit_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(modifier::Delimit)
