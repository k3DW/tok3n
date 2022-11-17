#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Into)

using namespace samples::all;

void prefix()
{
	assert
		, int1 == into<Class1>(spacedot)
		, int2 == into<Class2>(abc >> spacedot)
		;
}

void infix()
{
	assert
		, int1 == spacedot % into<Class1>
		, int2 == (abc >> spacedot) % into<Class2>
		;
}



void into_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(modifier::Into)
