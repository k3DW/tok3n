#include "pch.h"

TEST("Join", "Requirements")
{
	assert
		, IsParser<Joi1, JoinType, std::string_view>
		, IsParser<Joi2, JoinType, std::string_view>
		, IsParser<Joi3, JoinType, std::string_view>
		, IsParser<Joi4, JoinType, std::string_view>
		, IsParser<Joi5, JoinType, std::string_view>
		;
}

TEST("Join", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Joi1, "abcabc", "abc", "abc");
	ASSERT_PARSE_FAILURE(Joi1, "Abcabc");
	ASSERT_PARSE_FAILURE(Joi1, " abcabc");

	ASSERT_PARSE_SUCCESS(Joi2, "abcabcabcab", "abcabcabc", "ab");
	ASSERT_PARSE_FAILURE(Joi2, "");
	ASSERT_PARSE_FAILURE(Joi2, "ab");
	ASSERT_PARSE_SUCCESS(Joi2, "abc", "abc", "");

	ASSERT_PARSE_SUCCESS(Joi3, "abcabc", "abc", "abc");
	ASSERT_PARSE_SUCCESS(Joi3, "a??bcabc", "", "a??bcabc");
	ASSERT_PARSE_SUCCESS(Joi3, "", "", "");
	ASSERT_PARSE_SUCCESS(Joi3, "??abcabc", "??", "abcabc");
	ASSERT_PARSE_SUCCESS(Joi3, " ??abcabc", "", " ??abcabc");

	ASSERT_PARSE_SUCCESS(Joi4, "abc???????", "abc??????", "?");
	ASSERT_PARSE_FAILURE(Joi4, "??abc???????");
	ASSERT_PARSE_SUCCESS(Joi4, "abc??abc???????", "abc??", "abc???????");
	ASSERT_PARSE_SUCCESS(Joi4, "abc ??abc???????", "abc", " ??abc???????");
	ASSERT_PARSE_FAILURE(Joi4, "");

	ASSERT_PARSE_SUCCESS(Joi5, "abcabcabcabc??", "abcabcabcabc??", "");
	ASSERT_PARSE_SUCCESS(Joi5, "abcabcabcabc", "abcabcabcabc", "");
	ASSERT_PARSE_SUCCESS(Joi5, "abcabcabcabc ??", "abcabcabcabc", " ??");
	ASSERT_PARSE_SUCCESS(Joi5, "abc", "abc", "");
	ASSERT_PARSE_FAILURE(Joi5, " abc");
	ASSERT_PARSE_FAILURE(Joi5, "");
}
