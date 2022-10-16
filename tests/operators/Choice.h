#include "tests/utility.h"
#include "tests/common.h"

TOK3N_BEGIN_NAMESPACE_TESTS(operators::Choice)

void OneChar_and_OneChar()
{
	using namespace samples::basic;
	assert
		, (oc1 | oc2) == (oc2 | oc1)
		, (oc1 | oc3) == (oc3 | oc1)
		, (oc2 | oc3) == (oc3 | oc2)
		, (oc1 | oc2) == OneChar<"abcd">{}
		, (oc1 | oc3) == OneChar<"abcxyz">{}
		, (oc2 | oc3) == OneChar<"bcdxyz">{}
		, (oc1 | oc1) == oc1
		, (oc2 | oc2) == oc2
		, (oc3 | oc3) == oc3
		;
}

void NotChar_and_NotChar()
{
	using namespace samples::basic;
	assert
		, (nc1 | nc2) == (nc2 | nc1)
		, (nc1 | nc3) == (nc3 | nc1)
		, (nc2 | nc3) == (nc3 | nc2)
		, (nc1 | nc2) == NotChar<"bc">{}
		, (nc1 | nc3) == OneChar<every_char>{}
		, (nc2 | nc3) == OneChar<every_char>{}
		, (nc1 | nc1) == nc1
		, (nc2 | nc2) == nc2
		, (nc3 | nc3) == nc3
		;
}

void OneChar_and_NotChar()
{
	using namespace samples::basic;
	assert
		, (oc1 | nc1) == (nc1 | oc1)
		, (oc1 | nc2) == (nc2 | oc1)
		, (oc1 | nc3) == (nc3 | oc1)
		, (oc2 | nc1) == (nc1 | oc2)
		, (oc2 | nc2) == (nc2 | oc2)
		, (oc2 | nc3) == (nc3 | oc2)
		, (oc3 | nc1) == (nc1 | oc3)
		, (oc3 | nc2) == (nc2 | oc3)
		, (oc3 | nc3) == (nc3 | oc3)
		, (oc1 | nc1) == OneChar<every_char>{}
		, (oc1 | nc2) == NotChar<"d">{}
		, (oc1 | nc3) == NotChar<"xyz">{}
		, (oc2 | nc1) == NotChar<"a">{}
		, (oc2 | nc2) == OneChar<every_char>{}
		, (oc2 | nc3) == NotChar<"xyz">{}
		, (oc3 | nc1) == NotChar<"abc">{}
		, (oc3 | nc2) == NotChar<"bcd">{}
		, (oc3 | nc3) == OneChar<every_char>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(operators::Choice)
