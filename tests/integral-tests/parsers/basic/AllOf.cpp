#include "integral-tests/samples.h"

using L = AllOf<StaticArray(X, Y, Z)>;

FIXTURE("AllOf");

TEST("AllOf", "Requirements")
{
	ASSERT_IS_PARSER(L, value_type, AllOfFamily, Output<value_type>);
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

	ASSERT_PARSE_SUCCESS(AllOf<(StaticArray<value_type, 0>{})>, e(A, B, C), e(), e(A, B, C));
	ASSERT_PARSE_SUCCESS(AllOf<(StaticArray<value_type, 0>{})>, e(), e(), e());
}
