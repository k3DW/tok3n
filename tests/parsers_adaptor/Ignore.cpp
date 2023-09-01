#include "pch.h"

FIXTURE("Ignore");

TEST("Ignore", "Requirements")
{
	ASSERT_IS_PARSER(Ign1, IgnoreType, void);
	ASSERT_IS_PARSER(Ign2, IgnoreType, void);
	ASSERT_IS_PARSER(Ign3, IgnoreType, void);
	ASSERT_IS_PARSER(Ign4, IgnoreType, void);
	ASSERT_IS_PARSER(Ign5, IgnoreType, void);
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
