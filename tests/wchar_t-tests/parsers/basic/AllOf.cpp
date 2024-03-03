#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

using L = AllOf<L"literal">;

FIXTURE("AllOf");

TEST("AllOf", "Requirements")
{
	ASSERT_IS_PARSER(L, AllOfFamily, Output<wchar_t>);
}

TEST("AllOf", "Parse 'literal'")
{
	ASSERT_PARSE_SUCCESS(L, L"literal", L"literal", L"");
	ASSERT_PARSE_SUCCESS(L, L"literally", L"literal", L"ly");
	ASSERT_PARSE_FAILURE(L, L"litera");
	ASSERT_PARSE_FAILURE(L, L" literal");
	ASSERT_PARSE_FAILURE(L, L"LITERAL");
	ASSERT_PARSE_FAILURE(L, L"LITERALLY");
}



TEST("AllOf", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AllOf, L"");

	ASSERT_PARSE_SUCCESS(AllOf<L"">, L"anything", L"", L"anything");
	ASSERT_PARSE_SUCCESS(AllOf<L"">, L"", L"", L"");
}
