#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Constant");

TEST("Constant", "Requirements")
{
	ASSERT_IS_PARSER(Con1, ConstantFamily, int);
	ASSERT_IS_PARSER(Con2, ConstantFamily, char);
	ASSERT_IS_PARSER(Con3, ConstantFamily, bool);
	ASSERT_IS_PARSER(Con4, ConstantFamily, std::nullptr_t);
}

TEST("Constant", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Con1, L"abcabcabcab", 1, L"ab");
	ASSERT_PARSE_FAILURE(Con1, L"");
	ASSERT_PARSE_FAILURE(Con1, L"ab");
	ASSERT_PARSE_SUCCESS(Con1, L"abc", 1, L"");

	ASSERT_PARSE_SUCCESS(Con2, L"abcabc", L't', L"abc");
	ASSERT_PARSE_SUCCESS(Con2, L"a??bcabc", L't', L"a??bcabc");
	ASSERT_PARSE_SUCCESS(Con2, L"", L't', L"");
	ASSERT_PARSE_SUCCESS(Con2, L"??abcabc", L't', L"abcabc");
	ASSERT_PARSE_SUCCESS(Con2, L" ??abcabc", L't', L" ??abcabc");

	ASSERT_PARSE_SUCCESS(Con3, L"abc???????", true, L"?");
	ASSERT_PARSE_FAILURE(Con3, L"??abc???????");
	ASSERT_PARSE_SUCCESS(Con3, L"abc??abc???????", true, L"abc???????");
	ASSERT_PARSE_SUCCESS(Con3, L"abc ??abc???????", true, L" ??abc???????");
	ASSERT_PARSE_FAILURE(Con3, L"");

	ASSERT_PARSE_SUCCESS(Con4, L"abcabcabcabc??", nullptr, L"");
	ASSERT_PARSE_SUCCESS(Con4, L"abcabcabcabc", nullptr, L"");
	ASSERT_PARSE_SUCCESS(Con4, L"abcabcabcabc ??", nullptr, L" ??");
	ASSERT_PARSE_SUCCESS(Con4, L"abc", nullptr, L"");
	ASSERT_PARSE_FAILURE(Con4, L" abc");
	ASSERT_PARSE_FAILURE(Con4, L"");
}
