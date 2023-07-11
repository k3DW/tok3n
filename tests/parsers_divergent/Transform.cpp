#include "pch.h"

TEST("Transform", "Requirements")
{
	ASSERT_IS_PARSER(Tra1, TransformType, std::size_t);
	ASSERT_IS_PARSER(Tra2, TransformType, std::vector<char>);
	ASSERT_IS_PARSER(Tra3, TransformType, bool);
	ASSERT_IS_PARSER(Tra4, TransformType, std::size_t);
}

TEST("Transform", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Tra1, "abcabcabcab", 3, "ab");
	ASSERT_PARSE_FAILURE(Tra1, "");
	ASSERT_PARSE_FAILURE(Tra1, "ab");
	ASSERT_PARSE_SUCCESS(Tra1, "abc", 1, "");
		
	ASSERT_PARSE_SUCCESS(Tra2, "abcabc", std::vector({ 'a', 'b', 'c' }), "abc");
	ASSERT_PARSE_SUCCESS(Tra2, "a??bcabc", std::vector<char>{}, "a??bcabc");
	ASSERT_PARSE_SUCCESS(Tra2, "", std::vector<char>{}, "");
	ASSERT_PARSE_SUCCESS(Tra2, "??abcabc", std::vector<char>({ '?', '?' }), "abcabc");
	ASSERT_PARSE_SUCCESS(Tra2, " ??abcabc", std::vector<char>{}, " ??abcabc");
		
	ASSERT_PARSE_SUCCESS(Tra3, "abc???????", false, "?");
	ASSERT_PARSE_FAILURE(Tra3, "??abc???????");
	ASSERT_PARSE_SUCCESS(Tra3, "abc??abc???????", false, "abc???????");
	ASSERT_PARSE_SUCCESS(Tra3, "abc ??abc???????", true, " ??abc???????");
	ASSERT_PARSE_FAILURE(Tra3, "");
		
	ASSERT_PARSE_SUCCESS(Tra4, "abcabcabcabc??", 36, "");
	ASSERT_PARSE_SUCCESS(Tra4, "abcabcabcabc", 12, "");
	ASSERT_PARSE_SUCCESS(Tra4, "abcabcabcabc ??", 12, " ??");
	ASSERT_PARSE_SUCCESS(Tra4, "abc", 3, "");
	ASSERT_PARSE_FAILURE(Tra4, " abc");
	ASSERT_PARSE_FAILURE(Tra4, "");
}
