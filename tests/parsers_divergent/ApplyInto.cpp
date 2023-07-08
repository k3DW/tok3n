#include "pch.h"

TEST("ApplyInto", "Requirements")
{
	assert
		, IsParser<Api1, ApplyIntoType, Class2>
		, IsParser<Api2, ApplyIntoType, Class5>
		;
}

TEST("ApplyInto", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Api1, "abc.", Class2("abc", "."), "");
	ASSERT_PARSE_SUCCESS(Api1, "abc . ", Class2("abc", " "), ". ");
	ASSERT_PARSE_FAILURE(Api1, "");
	ASSERT_PARSE_FAILURE(Api1, "abc");

	ASSERT_PARSE_SUCCESS(Api2, ".abc", Class5(".", "abc"), "");
	ASSERT_PARSE_SUCCESS(Api2, " abc. ", Class5(" ", "abc"), ". ");
	ASSERT_PARSE_FAILURE(Api2, ".");
	ASSERT_PARSE_FAILURE(Api2, "abc");
}
