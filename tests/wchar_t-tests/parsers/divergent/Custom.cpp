#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Custom");

TEST("Custom", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Cus1, wchar_t);
	ASSERT_PARSER_VALUE_TYPE(Cus2, wchar_t);

	ASSERT_IS_PARSER(Cus1, char, CustomFamily, std::size_t);
	ASSERT_IS_PARSER(Cus2, char, CustomFamily, std::size_t);

	ASSERT_IS_PARSER(Cus1, wchar_t, CustomFamily, std::size_t);
	ASSERT_IS_PARSER(Cus2, wchar_t, CustomFamily, std::size_t);

	ASSERT_IS_PARSER(Cus1, int, CustomFamily, std::size_t);
	ASSERT_IS_PARSER(Cus2, int, CustomFamily, std::size_t);
}

TEST("Custom", "Parse Cus1")
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

TEST("Custom", "Parse Cus2")
{
	ASSERT_PARSE_SUCCESS(Cus2, "abc", (std::size_t)0, "bc");
	ASSERT_PARSE_SUCCESS(Cus2, "bca", (std::size_t)0, "ca");
	ASSERT_PARSE_SUCCESS(Cus2, "cab", (std::size_t)0, "ab");
	ASSERT_PARSE_FAILURE(Cus2, "xyz");
	ASSERT_PARSE_FAILURE(Cus2, "");

	ASSERT_PARSE_SUCCESS(Cus2, L"abc", (std::size_t)0, L"bc");
	ASSERT_PARSE_SUCCESS(Cus2, L"bca", (std::size_t)0, L"ca");
	ASSERT_PARSE_SUCCESS(Cus2, L"cab", (std::size_t)0, L"ab");
	ASSERT_PARSE_FAILURE(Cus2, L"xyz");
	ASSERT_PARSE_FAILURE(Cus2, L"");

	ASSERT_PARSE_SUCCESS(Cus2, e<int>("abc"), (std::size_t)0, e<int>("bc"));
	ASSERT_PARSE_SUCCESS(Cus2, e<int>("bca"), (std::size_t)0, e<int>("ca"));
	ASSERT_PARSE_SUCCESS(Cus2, e<int>("cab"), (std::size_t)0, e<int>("ab"));
	ASSERT_PARSE_FAILURE(Cus2, e<int>("xyz"));
	ASSERT_PARSE_FAILURE(Cus2, e<int>(""));
}
