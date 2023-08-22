#include "pch.h"

FIXTURE("ApplyTransform");

TEST("ApplyTransform", "Requirements")
{
	ASSERT_IS_PARSER(Apt1, ApplyTransformType, bool);
	ASSERT_IS_PARSER(Apt2, ApplyTransformType, std::size_t);
}

TEST("ApplyTransform", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Apt1, "abc???????", false, "?");
	ASSERT_PARSE_FAILURE(Apt1, "??abc???????");
	ASSERT_PARSE_SUCCESS(Apt1, "abc??abc???????", false, "abc???????");
	ASSERT_PARSE_SUCCESS(Apt1, "abc ??abc???????", true, " ??abc???????");
	ASSERT_PARSE_FAILURE(Apt1, "");

	ASSERT_PARSE_SUCCESS(Apt2, "abcabcabcabc??", 36, "");
	ASSERT_PARSE_SUCCESS(Apt2, "abcabcabcabc", 12, "");
	ASSERT_PARSE_SUCCESS(Apt2, "abcabcabcabc ??", 12, " ??");
	ASSERT_PARSE_SUCCESS(Apt2, "abc", 3, "");
	ASSERT_PARSE_FAILURE(Apt2, " abc");
	ASSERT_PARSE_FAILURE(Apt2, "");
}
