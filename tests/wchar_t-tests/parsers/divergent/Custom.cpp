#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Custom");

TEST("Custom", "Requirements")
{
	ASSERT_IS_PARSER(Cus1, CustomFamily, std::size_t);
}

TEST("Custom", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Cus1, L"abcabcabcabc??", 36, L"");
	ASSERT_PARSE_SUCCESS(Cus1, L"abcabcabcabc", 12, L"");
	ASSERT_PARSE_SUCCESS(Cus1, L"abcabcabcabc ??", 12, L" ??");
	ASSERT_PARSE_SUCCESS(Cus1, L"abc", 3, L"");
	ASSERT_PARSE_FAILURE(Cus1, L" abc");
	ASSERT_PARSE_FAILURE(Cus1, L"");
}
