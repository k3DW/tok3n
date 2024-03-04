#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("ApplyInto");

TEST("ApplyInto", "Requirements")
{
	ASSERT_IS_PARSER(Api1, ApplyIntoFamily, Class2);
	ASSERT_IS_PARSER(Api2, ApplyIntoFamily, Class5);
}

TEST("ApplyInto", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Api1, L"abc.", Class2(L"abc", L"."), L"");
	ASSERT_PARSE_SUCCESS(Api1, L"abc . ", Class2(L"abc", L" "), L". ");
	ASSERT_PARSE_FAILURE(Api1, L"");
	ASSERT_PARSE_FAILURE(Api1, L"abc");

	ASSERT_PARSE_SUCCESS(Api2, L".abc", Class5(L".", L"abc"), L"");
	ASSERT_PARSE_SUCCESS(Api2, L" abc. ", Class5(L" ", L"abc"), L". ");
	ASSERT_PARSE_FAILURE(Api2, L".");
	ASSERT_PARSE_FAILURE(Api2, L"abc");
}

TEST("ApplyInto", "Move only")
{
	using tuple = std::tuple<Output<wchar_t>, Output<wchar_t>>;
	using T = MoveOnlyWrapper<tuple>;
	using P = ApplyInto<Sequence<Any3, ABC>, T>;

	ASSERT_PARSE_SUCCESS(P, L"xabcd", T(std::tuple(L"x", L"abc")), L"d");
	ASSERT_PARSE_FAILURE(P, L"ydcba");
	ASSERT_PARSE_SUCCESS(P, L"zabcabcd", T(std::tuple(L"z", L"abc")), L"abcd");
}

TEST("ApplyInto", "Copy only")
{
	using tuple = std::tuple<Output<wchar_t>, Output<wchar_t>>;
	using T = CopyOnlyWrapper<tuple>;
	using P = ApplyInto<Sequence<Any3, ABC>, T>;

	ASSERT_PARSE_SUCCESS(P, L"xabcd", T(std::tuple(L"x", L"abc")), L"d");
	ASSERT_PARSE_FAILURE(P, L"ydcba");
	ASSERT_PARSE_SUCCESS(P, L"zabcabcd", T(std::tuple(L"z", L"abc")), L"abcd");
}
