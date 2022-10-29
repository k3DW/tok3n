#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(operators::Sequence)

using namespace samples::all;

void Literal_and_Literal()
{
	assert
		, (l1 >> l1) == Literal<"literalliteral">{}
		, (l1 >> l2) == Literal<"literally">{}
		, (l1 >> l3) == Literal<"literaltest">{}
		, (l2 >> l1) == Literal<"lyliteral">{}
		, (l2 >> l2) == Literal<"lyly">{}
		, (l2 >> l3) == Literal<"lytest">{}
		, (l3 >> l1) == Literal<"testliteral">{}
		, (l3 >> l2) == Literal<"testly">{}
		, (l3 >> l3) == Literal<"testtest">{}
		;
}



void Sequence_and_Sequence()
{
	assert
		, (seq1 >> seq1) == Sequence<L4, NC4, L4, NC4>{}
		, (seq2 >> seq2) == Sequence<NC4, L4, NC4, L4>{}
		, (seq3 >> seq3) == Sequence<L4, OC4, NC5, L4, OC4, NC5>{}
		, (seq4 >> seq4) == Sequence<NC5, L4, OC4, NC5, L4, OC4>{}
		, (seq1 >> seq2) == Sequence<L4, NC4, NC4, L4>{}
		, (seq2 >> seq1) == Sequence<NC4, L4, L4, NC4>{}
		, (seq1 >> seq3) == Sequence<L4, NC4, L4, OC4, NC5>{}
		, (seq3 >> seq1) == Sequence<L4, OC4, NC5, L4, NC4>{}
		, (seq1 >> seq4) == Sequence<L4, NC4, NC5, L4, OC4>{}
		, (seq4 >> seq1) == Sequence<NC5, L4, OC4, L4, NC4>{}
		, (seq2 >> seq3) == Sequence<NC4, L4, L4, OC4, NC5>{}
		, (seq3 >> seq2) == Sequence<L4, OC4, NC5, NC4, L4>{}
		, (seq2 >> seq4) == Sequence<NC4, L4, NC5, L4, OC4>{}
		, (seq4 >> seq2) == Sequence<NC5, L4, OC4, NC4, L4>{}
		, (seq3 >> seq4) == Sequence<L4, OC4, NC5, NC5, L4, OC4>{}
		, (seq4 >> seq3) == Sequence<NC5, L4, OC4, L4, OC4, NC5>{}
		;
}

void Sequence_and_anything()
{
	assert
		, (seq1 >> oc1) == Sequence<L4, NC4, OC1>{}
		, (oc1 >> seq1) == Sequence<OC1, L4, NC4>{}
		, (seq2 >> oc4) == Sequence<NC4, L4, OC4>{}
		, (oc4 >> seq2) == Sequence<OC4, NC4, L4>{}
		, (seq3 >> oc3) == Sequence<L4, OC4, NC5, OC3>{}
		, (oc3 >> seq3) == Sequence<OC3, L4, OC4, NC5>{}
		, (seq4 >> oc2) == Sequence<NC5, L4, OC4, OC2>{}
		, (oc2 >> seq4) == Sequence<OC2, NC5, L4, OC4>{}
		;
}

void anything_and_anything()
{
	// TODO once everything is added to samples::all
}

TOK3N_END_NAMESPACE_TESTS(operators::Sequence)
