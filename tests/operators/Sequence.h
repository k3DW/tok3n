#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(operators::Sequence)

void Literal_and_Literal()
{
	using namespace samples::basic;
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

TOK3N_END_NAMESPACE_TESTS(operators::Sequence)
