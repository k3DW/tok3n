#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Defaulted");

TEST("Defaulted", "Requirements")
{
	ASSERT_IS_PARSER(Def1, DefaultedFamily, int);
	ASSERT_IS_PARSER(Def2, DefaultedFamily, Class3);
}

TEST("Defaulted", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Def1, L"abcabcabcab", 0, L"ab");
	ASSERT_PARSE_FAILURE(Def1, L"");
	ASSERT_PARSE_FAILURE(Def1, L"ab");
	ASSERT_PARSE_SUCCESS(Def1, L"abc", 0, L"");

	ASSERT_PARSE_SUCCESS(Def2, L"abcabc", Class3{}, L"abc");
	ASSERT_PARSE_SUCCESS(Def2, L"a??bcabc", Class3{}, L"a??bcabc");
	ASSERT_PARSE_SUCCESS(Def2, L"", Class3{}, L"");
	ASSERT_PARSE_SUCCESS(Def2, L"??abcabc", Class3{}, L"abcabc");
	ASSERT_PARSE_SUCCESS(Def2, L" ??abcabc", Class3{}, L" ??abcabc");
}
