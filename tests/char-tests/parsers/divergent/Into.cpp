#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("Into");

TEST("Into", "Requirements")
{
	ASSERT_IS_PARSER(Int1, IntoFamily, Class1);
	ASSERT_IS_PARSER(Int2, IntoFamily, Class2);
	ASSERT_IS_PARSER(Int3, IntoFamily, Class2);
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

TEST("Into", "Move only")
{
	using T = MoveOnlyWrapper<Output<char>>;
	using P = Into<ABC, T>;

	ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
	ASSERT_PARSE_FAILURE(P, "dcba");
	ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
}

TEST("Into", "Copy only")
{
	using T = CopyOnlyWrapper<Output<char>>;
	using P = Into<ABC, T>;

	ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
	ASSERT_PARSE_FAILURE(P, "dcba");
	ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
}
