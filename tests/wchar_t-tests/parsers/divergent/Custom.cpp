#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Custom");

TEST("Custom", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Cus1, wchar_t);

	ASSERT_IS_PARSER(Cus1, char, CustomFamily, std::size_t);

	ASSERT_IS_PARSER(Cus1, wchar_t, CustomFamily, std::size_t);

	ASSERT_IS_PARSER(Cus1, int, CustomFamily, std::size_t);
}

TEST("Custom", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Cus1, "abcabcabcabc??", 36, "");
	ASSERT_PARSE_SUCCESS(Cus1, "abcabcabcabc", 12, "");
	ASSERT_PARSE_SUCCESS(Cus1, "abcabcabcabc ??", 12, " ??");
	ASSERT_PARSE_SUCCESS(Cus1, "abc", 3, "");
	ASSERT_PARSE_FAILURE(Cus1, " abc");
	ASSERT_PARSE_FAILURE(Cus1, "");

	ASSERT_PARSE_SUCCESS(Cus1, L"abcabcabcabc??", 36, L"");
	ASSERT_PARSE_SUCCESS(Cus1, L"abcabcabcabc", 12, L"");
	ASSERT_PARSE_SUCCESS(Cus1, L"abcabcabcabc ??", 12, L" ??");
	ASSERT_PARSE_SUCCESS(Cus1, L"abc", 3, L"");
	ASSERT_PARSE_FAILURE(Cus1, L" abc");
	ASSERT_PARSE_FAILURE(Cus1, L"");

	ASSERT_PARSE_SUCCESS(Cus1, e<int>("abcabcabcabc??"), 36, e<int>(""));
	ASSERT_PARSE_SUCCESS(Cus1, e<int>("abcabcabcabc"), 12, e<int>(""));
	ASSERT_PARSE_SUCCESS(Cus1, e<int>("abcabcabcabc ??"), 12, e<int>(" ??"));
	ASSERT_PARSE_SUCCESS(Cus1, e<int>("abc"), 3, e<int>(""));
	ASSERT_PARSE_FAILURE(Cus1, e<int>(" abc"));
	ASSERT_PARSE_FAILURE(Cus1, e<int>(""));
}
