#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Ignore");

TEST("Ignore", "Requirements")
{
	ASSERT_IS_PARSER(Ign1, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign2, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign3, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign4, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign5, IgnoreFamily, void);
}

TEST("Ignore", "Parse all")
{
	ASSERT_PARSE_SUCCESS_VOID(Ign1, L"abcabc", L"abc");
	ASSERT_PARSE_FAILURE(Ign1, L"Abcabc");
	ASSERT_PARSE_FAILURE(Ign1, L" abcabc");

	ASSERT_PARSE_SUCCESS_VOID(Ign2, L"abcabcabcab", L"ab");
	ASSERT_PARSE_FAILURE(Ign2, L"");
	ASSERT_PARSE_FAILURE(Ign2, L"ab");
	ASSERT_PARSE_SUCCESS_VOID(Ign2, L"abc", L"");

	ASSERT_PARSE_SUCCESS_VOID(Ign3, L"abcabc", L"abc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, L"a??bcabc", L"a??bcabc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, L"", L"");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, L"??abcabc", L"abcabc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, L" ??abcabc", L" ??abcabc");

	ASSERT_PARSE_SUCCESS_VOID(Ign4, L"abc???????", L"?");
	ASSERT_PARSE_FAILURE(Ign4, L"??abc???????");
	ASSERT_PARSE_SUCCESS_VOID(Ign4, L"abc??abc???????", L"abc???????");
	ASSERT_PARSE_SUCCESS_VOID(Ign4, L"abc ??abc???????", L" ??abc???????");
	ASSERT_PARSE_FAILURE(Ign4, L"");

	ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abcabcabcabc??", L"");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abcabcabcabc", L"");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abcabcabcabc ??", L" ??");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abc", L"");
	ASSERT_PARSE_FAILURE(Ign5, L" abc");
	ASSERT_PARSE_FAILURE(Ign5, L"");
}
