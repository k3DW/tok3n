#include "pch.h"
#include "enum-samples/enum-samples.h"

using enum E;
using Single = NoneOf<StaticArray(A)>;
using Multi  = NoneOf<StaticArray(A, B, C)>;

FIXTURE("NoneOf");

TEST("NoneOf", "Requirements")
{
	ASSERT_IS_PARSER(Single, NoneOfFamily, Output<E>);
	ASSERT_IS_PARSER(Multi, NoneOfFamily, Output<E>);
}

TEST("NoneOf", "Parse single")
{
	ASSERT_PARSE_FAILURE(Single, e(A, B));
	ASSERT_PARSE_SUCCESS(Single, e(B, A), e(B), e(A));
	ASSERT_PARSE_FAILURE(Single, e(A, B, C));
	ASSERT_PARSE_SUCCESS(Single, e(Space, A), e(Space), e(A));
}

TEST("NoneOf", "Parse multi")
{
	ASSERT_PARSE_FAILURE(Multi, e(A, B, C));
	ASSERT_PARSE_FAILURE(Multi, e(A, C, B));
	ASSERT_PARSE_FAILURE(Multi, e(B, A, C));
	ASSERT_PARSE_FAILURE(Multi, e(B, C, A));
	ASSERT_PARSE_FAILURE(Multi, e(C, A, B));
	ASSERT_PARSE_FAILURE(Multi, e(C, B, A));
	ASSERT_PARSE_SUCCESS(Multi, e(X, Y, Z), e(X), e(Y, Z));
	ASSERT_PARSE_SUCCESS(Multi, e(X, Z, Y), e(X), e(Z, Y));
	ASSERT_PARSE_SUCCESS(Multi, e(Y, X, Z), e(Y), e(X, Z));
	ASSERT_PARSE_SUCCESS(Multi, e(Y, Z, X), e(Y), e(Z, X));
	ASSERT_PARSE_SUCCESS(Multi, e(Z, X, Y), e(Z), e(X, Y));
	ASSERT_PARSE_SUCCESS(Multi, e(Z, Y, X), e(Z), e(Y, X));
}



TEST("NoneOf", "Constructible from lexicographically sorted only")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(NoneOf, StaticArray(A, B, C));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, StaticArray(A, C, B));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, StaticArray(B, A, C));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, StaticArray(B, C, A));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, StaticArray(C, A, B));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, StaticArray(C, B, A));
}

TEST("NoneOf", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(NoneOf, L"");

	ASSERT_PARSE_SUCCESS(decltype(anything<E>), e(A, B, C), e(A), e(B, C));
	ASSERT_PARSE_FAILURE(decltype(anything<E>), e());
}
