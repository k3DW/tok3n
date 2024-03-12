#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("Custom");

TEST("Custom", "Requirements")
{
	ASSERT_IS_PARSER(Cus1, char, CustomFamily, std::size_t);
}

TEST("Custom", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Cus1, "abcabcabcabc??", 36, "");
	ASSERT_PARSE_SUCCESS(Cus1, "abcabcabcabc", 12, "");
	ASSERT_PARSE_SUCCESS(Cus1, "abcabcabcabc ??", 12, " ??");
	ASSERT_PARSE_SUCCESS(Cus1, "abc", 3, "");
	ASSERT_PARSE_FAILURE(Cus1, " abc");
	ASSERT_PARSE_FAILURE(Cus1, "");
}
