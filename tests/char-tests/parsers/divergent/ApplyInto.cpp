#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("ApplyInto");

TEST("ApplyInto", "Requirements")
{
	ASSERT_IS_PARSER(Api1, char, ApplyIntoFamily, Class2);
	ASSERT_IS_PARSER(Api2, char, ApplyIntoFamily, Class5);
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

TEST("ApplyInto", "Move only")
{
	using tuple = std::tuple<Output<char>, Output<char>>;
	using T = MoveOnlyWrapper<tuple>;
	using P = ApplyInto<Sequence<Any3, ABC>, T>;

	ASSERT_PARSE_SUCCESS(P, "xabcd", T(std::tuple("x", "abc")), "d");
	ASSERT_PARSE_FAILURE(P, "ydcba");
	ASSERT_PARSE_SUCCESS(P, "zabcabcd", T(std::tuple("z", "abc")), "abcd");
}

TEST("ApplyInto", "Copy only")
{
	using tuple = std::tuple<Output<char>, Output<char>>;
	using T = CopyOnlyWrapper<tuple>;
	using P = ApplyInto<Sequence<Any3, ABC>, T>;

	ASSERT_PARSE_SUCCESS(P, "xabcd", T(std::tuple("x", "abc")), "d");
	ASSERT_PARSE_FAILURE(P, "ydcba");
	ASSERT_PARSE_SUCCESS(P, "zabcabcd", T(std::tuple("z", "abc")), "abcd");
}
