#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Transform");

TEST("Transform", "Requirements")
{
	ASSERT_IS_PARSER(Tra1, wchar_t, TransformFamily, std::size_t);
	ASSERT_IS_PARSER(Tra2, wchar_t, TransformFamily, std::vector<wchar_t>);
	ASSERT_IS_PARSER(Tra3, wchar_t, TransformFamily, bool);
	ASSERT_IS_PARSER(Tra4, wchar_t, TransformFamily, std::size_t);
}

TEST("Transform", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Tra1, L"abcabcabcab", 3, L"ab");
	ASSERT_PARSE_FAILURE(Tra1, L"");
	ASSERT_PARSE_FAILURE(Tra1, L"ab");
	ASSERT_PARSE_SUCCESS(Tra1, L"abc", 1, L"");

	ASSERT_PARSE_SUCCESS(Tra2, L"abcabc", std::vector({ L'a', L'b', L'c' }), L"abc");
	ASSERT_PARSE_SUCCESS(Tra2, L"a??bcabc", std::vector<wchar_t>{}, L"a??bcabc");
	ASSERT_PARSE_SUCCESS(Tra2, L"", std::vector<wchar_t>{}, L"");
	ASSERT_PARSE_SUCCESS(Tra2, L"??abcabc", std::vector<wchar_t>({ L'?', L'?' }), L"abcabc");
	ASSERT_PARSE_SUCCESS(Tra2, L" ??abcabc", std::vector<wchar_t>{}, L" ??abcabc");

	ASSERT_PARSE_SUCCESS(Tra3, L"abc???????", false, L"?");
	ASSERT_PARSE_FAILURE(Tra3, L"??abc???????");
	ASSERT_PARSE_SUCCESS(Tra3, L"abc??abc???????", false, L"abc???????");
	ASSERT_PARSE_SUCCESS(Tra3, L"abc ??abc???????", true, L" ??abc???????");
	ASSERT_PARSE_FAILURE(Tra3, L"");

	ASSERT_PARSE_SUCCESS(Tra4, L"abcabcabcabc??", 36, L"");
	ASSERT_PARSE_SUCCESS(Tra4, L"abcabcabcabc", 12, L"");
	ASSERT_PARSE_SUCCESS(Tra4, L"abcabcabcabc ??", 12, L" ??");
	ASSERT_PARSE_SUCCESS(Tra4, L"abc", 3, L"");
	ASSERT_PARSE_FAILURE(Tra4, L" abc");
	ASSERT_PARSE_FAILURE(Tra4, L"");
}

TEST("Transform", "Move only")
{
	using T = MoveOnlyWrapper<Output<wchar_t>>;
	using P = Transform<ABC, Const<T::make>>;

	ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
	ASSERT_PARSE_FAILURE(P, L"dcba");
	ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
}

TEST("Transform", "Copy only")
{
	using T = CopyOnlyWrapper<Output<wchar_t>>;
	using P = Transform<ABC, Const<T::make>>;

	ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
	ASSERT_PARSE_FAILURE(P, L"dcba");
	ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
}
