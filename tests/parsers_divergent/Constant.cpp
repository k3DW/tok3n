#include "pch.h"

TEST("Constant", "Requirements")
{
	assert
		, IsParser<Con1, ConstantType, int>
		, IsParser<Con2, ConstantType, char>
		, IsParser<Con3, ConstantType, bool>
		, IsParser<Con4, ConstantType, std::nullptr_t>
		;
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
