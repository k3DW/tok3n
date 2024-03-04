#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Into");

TEST("Into", "Requirements")
{
	ASSERT_IS_PARSER(Int1, IntoFamily, Class1);
	ASSERT_IS_PARSER(Int2, IntoFamily, Class2);
	ASSERT_IS_PARSER(Int3, IntoFamily, Class2);
}

TEST("Into", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Int1, L" ", Class1(0), L"");
	ASSERT_PARSE_FAILURE(Int1, L"a");
	ASSERT_PARSE_SUCCESS(Int1, L".", Class1(1), L"");
	ASSERT_PARSE_FAILURE(Int1, L"");

	ASSERT_PARSE_SUCCESS(Int2, L"abc.", Class2(L"abc", L"."), L"");
	ASSERT_PARSE_SUCCESS(Int2, L"abc . ", Class2(L"abc", L" "), L". ");
	ASSERT_PARSE_FAILURE(Int2, L"");
	ASSERT_PARSE_FAILURE(Int2, L"abc");

	ASSERT_PARSE_SUCCESS(Int3, L"abc.", Class2(L"abc", L"."), L"");
	ASSERT_PARSE_SUCCESS(Int3, L"abc . ", Class2(L"abc", L" "), L". ");
	ASSERT_PARSE_FAILURE(Int3, L"");
	ASSERT_PARSE_FAILURE(Int3, L"abc");
}

TEST("Into", "Move only")
{
	using T = MoveOnlyWrapper<Output<wchar_t>>;
	using P = Into<ABC, T>;

	ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
	ASSERT_PARSE_FAILURE(P, L"dcba");
	ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
}

TEST("Into", "Copy only")
{
	using T = CopyOnlyWrapper<Output<wchar_t>>;
	using P = Into<ABC, T>;

	ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
	ASSERT_PARSE_FAILURE(P, L"dcba");
	ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
}
