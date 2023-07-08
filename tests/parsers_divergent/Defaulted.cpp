#include "pch.h"

TEST("Defaulted", "Requirements")
{
	assert
		, IsParser<Def1, DefaultedType, int>
		, IsParser<Def2, DefaultedType, Class3>
		;
}

TEST("Defaulted", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Def1, "abcabcabcab", 0, "ab");
	ASSERT_PARSE_FAILURE(Def1, "");
	ASSERT_PARSE_FAILURE(Def1, "ab");
	ASSERT_PARSE_SUCCESS(Def1, "abc", 0, "");

	ASSERT_PARSE_SUCCESS(Def2, "abcabc", Class3{}, "abc");
	ASSERT_PARSE_SUCCESS(Def2, "a??bcabc", Class3{}, "a??bcabc");
	ASSERT_PARSE_SUCCESS(Def2, "", Class3{}, "");
	ASSERT_PARSE_SUCCESS(Def2, "??abcabc", Class3{}, "abcabc");
	ASSERT_PARSE_SUCCESS(Def2, " ??abcabc", Class3{}, " ??abcabc");
}
