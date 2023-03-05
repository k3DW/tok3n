#ifdef TOK3N_TESTING
#include "pch.h"

TOK3N_BEGIN_NAMESPACE_TESTS(regular::Choice)

using namespace samples::all;

void OneChar_and_OneChar()
{
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



void Choice_and_Choice()
{
	assert
		, (cho1 | cho1) == cho1
		, (cho2 | cho2) == cho2
		, (cho3 | cho3) == cho3
		, (cho4 | cho4) == cho4
		, (cho1 | cho2) == Choice<L4, NC4, NC4, L4>{}
		, (cho2 | cho1) == Choice<NC4, L4, L4, NC4>{}
		, (cho1 | cho3) == Choice<L4, NC4, L4, OC4, NC5>{}
		, (cho3 | cho1) == Choice<L4, OC4, NC5, L4, NC4>{}
		, (cho1 | cho4) == Choice<L4, NC4, NC5, L4, OC4>{}
		, (cho4 | cho1) == Choice<NC5, L4, OC4, L4, NC4>{}
		, (cho2 | cho3) == Choice<NC4, L4, L4, OC4, NC5>{}
		, (cho3 | cho2) == Choice<L4, OC4, NC5, NC4, L4>{}
		, (cho2 | cho4) == Choice<NC4, L4, NC5, L4, OC4>{}
		, (cho4 | cho2) == Choice<NC5, L4, OC4, NC4, L4>{}
		, (cho3 | cho4) == Choice<L4, OC4, NC5, NC5, L4, OC4>{}
		, (cho4 | cho3) == Choice<NC5, L4, OC4, L4, OC4, NC5>{}
		;
}

void Choice_and_anything()
{
	assert
		, (cho1 | oc1) == Choice<L4, NC4, OC1>{}
		, (oc1 | cho1) == Choice<OC1, L4, NC4>{}
		, (cho2 | oc4) == Choice<NC4, L4, OC4>{}
		, (oc4 | cho2) == Choice<OC4, NC4, L4>{}
		, (cho3 | oc3) == Choice<L4, OC4, NC5, OC3>{}
		, (oc3 | cho3) == Choice<OC3, L4, OC4, NC5>{}
		, (cho4 | oc2) == Choice<NC5, L4, OC4, OC2>{}
		, (oc2 | cho4) == Choice<OC2, NC5, L4, OC4>{}
		;
}

template <auto p1, auto p2>
constexpr bool operator_is_not_valid = not requires { p1 | p2; };

void anything_and_anything()
{
	// I would like to add tests for everything,
	// but it's infeasible to do all combinations of samples.
	// I might set up some sort of code generation later.
	assert
		, operator_is_not_valid<cho1, seq1>
		, operator_is_not_valid<seq1, cho1>
		;
}

void void_result()
{
	constexpr auto void_choice = (ign1 | ign2);

	assert
		, void_choice == Choice<Ign1, Ign2>{}
		, result_of<decltype(void_choice)>.is<void>
		, parse(void_choice, "abcabcabcdabcd").success("abcabcdabcd")
		;
}

TOK3N_END_NAMESPACE_TESTS(regular::Choice)

#endif
