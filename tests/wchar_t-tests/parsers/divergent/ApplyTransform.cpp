#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("ApplyTransform");

TEST("ApplyTransform", "Requirements")
{
	ASSERT_IS_PARSER(Apt1, wchar_t, ApplyTransformFamily, bool);
	ASSERT_IS_PARSER(Apt2, wchar_t, ApplyTransformFamily, std::size_t);
}

TEST("ApplyTransform", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Apt1, L"abc???????", false, L"?");
	ASSERT_PARSE_FAILURE(Apt1, L"??abc???????");
	ASSERT_PARSE_SUCCESS(Apt1, L"abc??abc???????", false, L"abc???????");
	ASSERT_PARSE_SUCCESS(Apt1, L"abc ??abc???????", true, L" ??abc???????");
	ASSERT_PARSE_FAILURE(Apt1, L"");

	ASSERT_PARSE_SUCCESS(Apt2, L"abcabcabcabc??", 36, L"");
	ASSERT_PARSE_SUCCESS(Apt2, L"abcabcabcabc", 12, L"");
	ASSERT_PARSE_SUCCESS(Apt2, L"abcabcabcabc ??", 12, L" ??");
	ASSERT_PARSE_SUCCESS(Apt2, L"abc", 3, L"");
	ASSERT_PARSE_FAILURE(Apt2, L" abc");
	ASSERT_PARSE_FAILURE(Apt2, L"");
}

TEST("ApplyTransform", "Move only")
{
	using tuple = std::tuple<Output<wchar_t>, Output<wchar_t>>;
	using T = MoveOnlyWrapper<tuple>;
	using P = ApplyTransform<Sequence<Any3, ABC>, Const<T::make>>;

	ASSERT_PARSE_SUCCESS(P, L"xabcd", T(std::tuple(L"x", L"abc")), L"d");
	ASSERT_PARSE_FAILURE(P, L"ydcba");
	ASSERT_PARSE_SUCCESS(P, L"zabcabcd", T(std::tuple(L"z", L"abc")), L"abcd");
}

TEST("ApplyTransform", "Copy only")
{
	using tuple = std::tuple<Output<wchar_t>, Output<wchar_t>>;
	using T = CopyOnlyWrapper<tuple>;
	using P = ApplyTransform<Sequence<Any3, ABC>, Const<T::make>>;

	ASSERT_PARSE_SUCCESS(P, L"xabcd", T(std::tuple(L"x", L"abc")), L"d");
	ASSERT_PARSE_FAILURE(P, L"ydcba");
	ASSERT_PARSE_SUCCESS(P, L"zabcabcd", T(std::tuple(L"z", L"abc")), L"abcd");
}
