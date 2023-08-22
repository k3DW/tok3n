#include "pch.h"

FIXTURE("Into");

TEST("Into", "Requirements")
{
	ASSERT_IS_PARSER(Int1, IntoType, Class1);
	ASSERT_IS_PARSER(Int2, IntoType, Class2);
	ASSERT_IS_PARSER(Int3, IntoType, Class2);
}

TEST("Into", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Int1, " ", Class1(0), "");
	ASSERT_PARSE_FAILURE(Int1, "a");
	ASSERT_PARSE_SUCCESS(Int1, ".", Class1(1), "");
	ASSERT_PARSE_FAILURE(Int1, "");

	ASSERT_PARSE_SUCCESS(Int2, "abc.", Class2("abc", "."), "");
	ASSERT_PARSE_SUCCESS(Int2, "abc . ", Class2("abc", " "), ". ");
	ASSERT_PARSE_FAILURE(Int2, "");
	ASSERT_PARSE_FAILURE(Int2, "abc");

	ASSERT_PARSE_SUCCESS(Int3, "abc.", Class2("abc", "."), "");
	ASSERT_PARSE_SUCCESS(Int3, "abc . ", Class2("abc", " "), ". ");
	ASSERT_PARSE_FAILURE(Int3, "");
	ASSERT_PARSE_FAILURE(Int3, "abc");
}
