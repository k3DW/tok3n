#include "pch.h"
#include "int-tests/samples.h"

using Single = AnyOf<StaticArray(A)>;
using Multi  = AnyOf<StaticArray(A, B, C)>;

FIXTURE("AnyOf");

TEST("AnyOf", "Requirements")
{
	ASSERT_IS_PARSER(Single, value_type, AnyOfFamily, Output<value_type>);
	ASSERT_IS_PARSER(Multi, value_type, AnyOfFamily, Output<value_type>);
}

TEST("AnyOf", "Parse single")
{
	ASSERT_PARSE_SUCCESS(Single, e(A, B), e(A), e(B));
	ASSERT_PARSE_FAILURE(Single, e(B, A));
	ASSERT_PARSE_SUCCESS(Single, e(A, B, C), e(A), e(B, C));
	ASSERT_PARSE_FAILURE(Single, e(Space, A));
}

TEST("AnyOf", "Parse multi")
{
	ASSERT_PARSE_SUCCESS(Multi, e(A, B, C), e(A), e(B, C));
	ASSERT_PARSE_SUCCESS(Multi, e(A, C, B), e(A), e(C, B));
	ASSERT_PARSE_SUCCESS(Multi, e(B, A, C), e(B), e(A, C));
	ASSERT_PARSE_SUCCESS(Multi, e(B, C, A), e(B), e(C, A));
	ASSERT_PARSE_SUCCESS(Multi, e(C, A, B), e(C), e(A, B));
	ASSERT_PARSE_SUCCESS(Multi, e(C, B, A), e(C), e(B, A));
	ASSERT_PARSE_FAILURE(Multi, e(X, Y, Z));
	ASSERT_PARSE_FAILURE(Multi, e(X, Z, Y));
	ASSERT_PARSE_FAILURE(Multi, e(Y, X, Z));
	ASSERT_PARSE_FAILURE(Multi, e(Y, Z, X));
	ASSERT_PARSE_FAILURE(Multi, e(Z, X, Y));
	ASSERT_PARSE_FAILURE(Multi, e(Z, Y, X));
}



TEST("AnyOf", "Constructible from lexicographically sorted only")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AnyOf, StaticArray(A, B, C));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, StaticArray(A, C, B));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, StaticArray(B, A, C));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, StaticArray(B, C, A));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, StaticArray(C, A, B));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, StaticArray(C, B, A));
}

TEST("AnyOf", "Parse")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AnyOf, L"");
	
	ASSERT_PARSE_FAILURE(AnyOf<(StaticArray<value_type, 0>{})>, e(A, B, C));
	ASSERT_PARSE_FAILURE(AnyOf<(StaticArray<value_type, 0>{})>, e());
}
