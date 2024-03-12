#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("ApplyTransform");

TEST("ApplyTransform", "Requirements")
{
	ASSERT_IS_PARSER(Apt1, char, ApplyTransformFamily, bool);
	ASSERT_IS_PARSER(Apt2, char, ApplyTransformFamily, std::size_t);
}

TEST("ApplyTransform", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Apt1, "abc???????", false, "?");
	ASSERT_PARSE_FAILURE(Apt1, "??abc???????");
	ASSERT_PARSE_SUCCESS(Apt1, "abc??abc???????", false, "abc???????");
	ASSERT_PARSE_SUCCESS(Apt1, "abc ??abc???????", true, " ??abc???????");
	ASSERT_PARSE_FAILURE(Apt1, "");

	ASSERT_PARSE_SUCCESS(Apt2, "abcabcabcabc??", 36, "");
	ASSERT_PARSE_SUCCESS(Apt2, "abcabcabcabc", 12, "");
	ASSERT_PARSE_SUCCESS(Apt2, "abcabcabcabc ??", 12, " ??");
	ASSERT_PARSE_SUCCESS(Apt2, "abc", 3, "");
	ASSERT_PARSE_FAILURE(Apt2, " abc");
	ASSERT_PARSE_FAILURE(Apt2, "");
}

TEST("ApplyTransform", "Move only")
{
	using tuple = std::tuple<Output<char>, Output<char>>;
	using T = MoveOnlyWrapper<tuple>;
	using P = ApplyTransform<Sequence<Any3, ABC>, Const<T::make>>;

	ASSERT_PARSE_SUCCESS(P, "xabcd", T(std::tuple("x", "abc")), "d");
	ASSERT_PARSE_FAILURE(P, "ydcba");
	ASSERT_PARSE_SUCCESS(P, "zabcabcd", T(std::tuple("z", "abc")), "abcd");
}

TEST("ApplyTransform", "Copy only")
{
	using tuple = std::tuple<Output<char>, Output<char>>;
	using T = CopyOnlyWrapper<tuple>;
	using P = ApplyTransform<Sequence<Any3, ABC>, Const<T::make>>;

	ASSERT_PARSE_SUCCESS(P, "xabcd", T(std::tuple("x", "abc")), "d");
	ASSERT_PARSE_FAILURE(P, "ydcba");
	ASSERT_PARSE_SUCCESS(P, "zabcabcd", T(std::tuple("z", "abc")), "abcd");
}
