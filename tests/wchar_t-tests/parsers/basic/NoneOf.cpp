#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

using Single = NoneOf<L'a'>;
using Multi  = NoneOf<L"abc">;

FIXTURE("NoneOf");

TEST("NoneOf", "Requirements")
{
	ASSERT_IS_PARSER(Single, NoneOfFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Multi, NoneOfFamily, Output<wchar_t>);
}

TEST("NoneOf", "Parse single")
{
	ASSERT_PARSE_FAILURE(Single, L"ab");
	ASSERT_PARSE_SUCCESS(Single, L"ba", L"b", L"a");
	ASSERT_PARSE_FAILURE(Single, L"abc");
	ASSERT_PARSE_SUCCESS(Single, L"Ab", L"A", L"b");
	ASSERT_PARSE_SUCCESS(Single, L"Abc", L"A", L"bc");
	ASSERT_PARSE_SUCCESS(Single, L" abc", L" ", L"abc");
}

TEST("NoneOf", "Parse multi")
{
	ASSERT_PARSE_FAILURE(Multi, L"abc");
	ASSERT_PARSE_FAILURE(Multi, L"acb");
	ASSERT_PARSE_FAILURE(Multi, L"bac");
	ASSERT_PARSE_FAILURE(Multi, L"bca");
	ASSERT_PARSE_FAILURE(Multi, L"cab");
	ASSERT_PARSE_FAILURE(Multi, L"cba");
	ASSERT_PARSE_SUCCESS(Multi, L"ABC", L"A", L"BC");
	ASSERT_PARSE_SUCCESS(Multi, L"ACB", L"A", L"CB");
	ASSERT_PARSE_SUCCESS(Multi, L"BAC", L"B", L"AC");
	ASSERT_PARSE_SUCCESS(Multi, L"BCA", L"B", L"CA");
	ASSERT_PARSE_SUCCESS(Multi, L"CAB", L"C", L"AB");
	ASSERT_PARSE_SUCCESS(Multi, L"CBA", L"C", L"BA");
	ASSERT_PARSE_SUCCESS(Multi, L"dcba", L"d", L"cba");
	ASSERT_PARSE_SUCCESS(Multi, L"edcba", L"e", L"dcba");
	ASSERT_PARSE_SUCCESS(Multi, L" cba", L" ", L"cba");
}



TEST("NoneOf", "Constructible from lexicographically sorted only")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(NoneOf, L"abc");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, L"acb");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, L"bac");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, L"bca");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, L"cab");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, L"cba");
}

TEST("NoneOf", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(NoneOf, L"");

	ASSERT_PARSE_SUCCESS(NoneOf<L"">, L"anything", L"a", L"nything");
	ASSERT_PARSE_FAILURE(NoneOf<L"">, L"");
}
