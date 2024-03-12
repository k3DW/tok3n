#include "pch.h"
#include "op_equals-samples/op_equals-samples.h"

using namespace SS;
using L = AllOf<StaticArray(X, Y, Z)>;

FIXTURE("AllOf");

TEST("AllOf", "Requirements")
{
	ASSERT_IS_PARSER(L, S, AllOfFamily, Output<S>);
}

TEST("AllOf", "Parse")
{
	ASSERT_PARSE_SUCCESS(L, e(X, Y, Z), e(X, Y, Z), e());
	ASSERT_PARSE_SUCCESS(L, e(X, Y, Z, A, B), e(X, Y, Z), e(A, B));
	ASSERT_PARSE_FAILURE(L, e(X, Y));
	ASSERT_PARSE_FAILURE(L, e(Space, X, Y));
}



TEST("AllOf", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AllOf, e());

	ASSERT_PARSE_SUCCESS(decltype(eps<S>), e(A, B, C), e(), e(A, B, C));
	ASSERT_PARSE_SUCCESS(decltype(eps<S>), e(), e(), e());
}
