#include "pch.h"

TEST("Ignore", "Requirements")
{
	assert
		, IsParser<Ign1, IgnoreType, void>
		, IsParser<Ign2, IgnoreType, void>
		, IsParser<Ign3, IgnoreType, void>
		, IsParser<Ign4, IgnoreType, void>
		, IsParser<Ign5, IgnoreType, void>
		;
}

TEST("Ignore", "Parse all")
{
	ASSERT_PARSE_SUCCESS_VOID(Ign1, "abcabc", "abc");
	ASSERT_PARSE_FAILURE(Ign1, "Abcabc");
	ASSERT_PARSE_FAILURE(Ign1, " abcabc");

	ASSERT_PARSE_SUCCESS_VOID(Ign2, "abcabcabcab", "ab");
	ASSERT_PARSE_FAILURE(Ign2, "");
	ASSERT_PARSE_FAILURE(Ign2, "ab");
	ASSERT_PARSE_SUCCESS_VOID(Ign2, "abc", "");

	ASSERT_PARSE_SUCCESS_VOID(Ign3, "abcabc", "abc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, "a??bcabc", "a??bcabc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, "", "");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, "??abcabc", "abcabc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, " ??abcabc", " ??abcabc");

	ASSERT_PARSE_SUCCESS_VOID(Ign4, "abc???????", "?");
	ASSERT_PARSE_FAILURE(Ign4, "??abc???????");
	ASSERT_PARSE_SUCCESS_VOID(Ign4, "abc??abc???????", "abc???????");
	ASSERT_PARSE_SUCCESS_VOID(Ign4, "abc ??abc???????", " ??abc???????");
	ASSERT_PARSE_FAILURE(Ign4, "");

	ASSERT_PARSE_SUCCESS_VOID(Ign5, "abcabcabcabc??", "");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, "abcabcabcabc", "");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, "abcabcabcabc ??", " ??");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, "abc", "");
	ASSERT_PARSE_FAILURE(Ign5, " abc");
	ASSERT_PARSE_FAILURE(Ign5, "");
}
