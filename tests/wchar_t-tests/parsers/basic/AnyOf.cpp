#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

using Single = AnyOf<L'a'>;
using Multi  = AnyOf<L"abc">;

FIXTURE("AnyOf");

TEST("AnyOf", "Requirements")
{
	ASSERT_IS_PARSER(Single, AnyOfFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Multi, AnyOfFamily, Output<wchar_t>);
}

TEST("AnyOf", "Parse single")
{
	ASSERT_PARSE_SUCCESS(Single, L"ab", L"a", L"b");
	ASSERT_PARSE_FAILURE(Single, L"ba");
	ASSERT_PARSE_SUCCESS(Single, L"abc", L"a", L"bc");
	ASSERT_PARSE_FAILURE(Single, L"Ab");
	ASSERT_PARSE_FAILURE(Single, L"Abc");
	ASSERT_PARSE_FAILURE(Single, L" abc");
}

TEST("AnyOf", "Parse multi")
{
	ASSERT_PARSE_SUCCESS(Multi, L"abc", L"a", L"bc");
	ASSERT_PARSE_SUCCESS(Multi, L"acb", L"a", L"cb");
	ASSERT_PARSE_SUCCESS(Multi, L"bac", L"b", L"ac");
	ASSERT_PARSE_SUCCESS(Multi, L"bca", L"b", L"ca");
	ASSERT_PARSE_SUCCESS(Multi, L"cab", L"c", L"ab");
	ASSERT_PARSE_SUCCESS(Multi, L"cba", L"c", L"ba");
	ASSERT_PARSE_FAILURE(Multi, L"ABC");
	ASSERT_PARSE_FAILURE(Multi, L"ACB");
	ASSERT_PARSE_FAILURE(Multi, L"BAC");
	ASSERT_PARSE_FAILURE(Multi, L"BCA");
	ASSERT_PARSE_FAILURE(Multi, L"CAB");
	ASSERT_PARSE_FAILURE(Multi, L"CBA");
	ASSERT_PARSE_FAILURE(Multi, L"dcba");
	ASSERT_PARSE_FAILURE(Multi, L" cba");
}



TEST("AnyOf", "Constructible from lexicographically sorted only")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AnyOf, L"abc");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, L"acb");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, L"bac");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, L"bca");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, L"cab");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, L"cba");
}

TEST("AnyOf", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AnyOf, L"");
	
	ASSERT_PARSE_FAILURE(AnyOf<L"">, L"anything");
	ASSERT_PARSE_FAILURE(AnyOf<L"">, L"");
}
