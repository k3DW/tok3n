#include "pch.h"
#include "char-samples/char-samples.h"

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
	ASSERT_PARSE_SUCCESS(Con1, "abcabcabcab", 1, "ab");
	ASSERT_PARSE_FAILURE(Con1, "");
	ASSERT_PARSE_FAILURE(Con1, "ab");
	ASSERT_PARSE_SUCCESS(Con1, "abc", 1, "");
		
	ASSERT_PARSE_SUCCESS(Con2, "abcabc", 't', "abc");
	ASSERT_PARSE_SUCCESS(Con2, "a??bcabc", 't', "a??bcabc");
	ASSERT_PARSE_SUCCESS(Con2, "", 't', "");
	ASSERT_PARSE_SUCCESS(Con2, "??abcabc", 't', "abcabc");
	ASSERT_PARSE_SUCCESS(Con2, " ??abcabc", 't', " ??abcabc");
		
	ASSERT_PARSE_SUCCESS(Con3, "abc???????", true, "?");
	ASSERT_PARSE_FAILURE(Con3, "??abc???????");
	ASSERT_PARSE_SUCCESS(Con3, "abc??abc???????", true, "abc???????");
	ASSERT_PARSE_SUCCESS(Con3, "abc ??abc???????", true, " ??abc???????");
	ASSERT_PARSE_FAILURE(Con3, "");
		
	ASSERT_PARSE_SUCCESS(Con4, "abcabcabcabc??", nullptr, "");
	ASSERT_PARSE_SUCCESS(Con4, "abcabcabcabc", nullptr, "");
	ASSERT_PARSE_SUCCESS(Con4, "abcabcabcabc ??", nullptr, " ??");
	ASSERT_PARSE_SUCCESS(Con4, "abc", nullptr, "");
	ASSERT_PARSE_FAILURE(Con4, " abc");
	ASSERT_PARSE_FAILURE(Con4, "");
}
