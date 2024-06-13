#include "pch.h"
#include "wchar_t-tests/samples.h"

FIXTURE("Transform");

TEST("Transform", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Tra1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Tra2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Tra3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Tra4, value_type);

	ASSERT_IS_NOT_PARSER(Tra1, char, TransformFamily);
	ASSERT_IS_PARSER(Tra2, char, TransformFamily, std::vector<char>);
	ASSERT_IS_PARSER(Tra3, char, TransformFamily, bool);
	ASSERT_IS_PARSER(Tra4, char, TransformFamily, std::size_t);

	ASSERT_IS_PARSER(Tra1, wchar_t, TransformFamily, std::size_t);
	ASSERT_IS_PARSER(Tra2, wchar_t, TransformFamily, std::vector<wchar_t>);
	ASSERT_IS_PARSER(Tra3, wchar_t, TransformFamily, bool);
	ASSERT_IS_PARSER(Tra4, wchar_t, TransformFamily, std::size_t);

	ASSERT_IS_NOT_PARSER(Tra1, int, TransformFamily);
	ASSERT_IS_PARSER(Tra2, int, TransformFamily, std::vector<int>);
	ASSERT_IS_PARSER(Tra3, int, TransformFamily, bool);
	ASSERT_IS_PARSER(Tra4, int, TransformFamily, std::size_t);
}

TEST("Transform", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Tra1, TT("abcabcabcab"), 3, TT("ab"));
	ASSERT_PARSE_FAILURE(Tra1, TT(""));
	ASSERT_PARSE_FAILURE(Tra1, TT("ab"));
	ASSERT_PARSE_SUCCESS(Tra1, TT("abc"), 1, TT(""));

	ASSERT_PARSE_SUCCESS(Tra2, "abcabc", std::vector<char>({ 'a', 'b', 'c' }), "abc");
	ASSERT_PARSE_SUCCESS(Tra2, "a??bcabc", std::vector<char>{}, "a??bcabc");
	ASSERT_PARSE_SUCCESS(Tra2, "", std::vector<char>{}, "");
	ASSERT_PARSE_SUCCESS(Tra2, "??abcabc", std::vector<char>({ '?', '?' }), "abcabc");
	ASSERT_PARSE_SUCCESS(Tra2, " ??abcabc", std::vector<char>{}, " ??abcabc");

	ASSERT_PARSE_SUCCESS(Tra3, "abc???????", false, "?");
	ASSERT_PARSE_FAILURE(Tra3, "??abc???????");
	ASSERT_PARSE_SUCCESS(Tra3, "abc??abc???????", false, "abc???????");
	ASSERT_PARSE_SUCCESS(Tra3, "abc ??abc???????", true, " ??abc???????");
	ASSERT_PARSE_FAILURE(Tra3, "");

	ASSERT_PARSE_SUCCESS(Tra4, "abcabcabcabc??", 36, "");
	ASSERT_PARSE_SUCCESS(Tra4, "abcabcabcabc", 12, "");
	ASSERT_PARSE_SUCCESS(Tra4, "abcabcabcabc ??", 12, " ??");
	ASSERT_PARSE_SUCCESS(Tra4, "abc", 3, "");
	ASSERT_PARSE_FAILURE(Tra4, " abc");
	ASSERT_PARSE_FAILURE(Tra4, "");

	ASSERT_PARSE_SUCCESS(Tra2, L"abcabc", std::vector<wchar_t>({ 'a', 'b', 'c' }), L"abc");
	ASSERT_PARSE_SUCCESS(Tra2, L"a??bcabc", std::vector<wchar_t>{}, L"a??bcabc");
	ASSERT_PARSE_SUCCESS(Tra2, L"", std::vector<wchar_t>{}, L"");
	ASSERT_PARSE_SUCCESS(Tra2, L"??abcabc", std::vector<wchar_t>({ '?', '?' }), L"abcabc");
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

	ASSERT_PARSE_SUCCESS(Tra2, e<int>("abcabc"), std::vector<int>({ 'a', 'b', 'c' }), e<int>("abc"));
	ASSERT_PARSE_SUCCESS(Tra2, e<int>("a??bcabc"), std::vector<int>{}, e<int>("a??bcabc"));
	ASSERT_PARSE_SUCCESS(Tra2, e<int>(""), std::vector<int>{}, e<int>(""));
	ASSERT_PARSE_SUCCESS(Tra2, e<int>("??abcabc"), std::vector<int>({ '?', '?' }), e<int>("abcabc"));
	ASSERT_PARSE_SUCCESS(Tra2, e<int>(" ??abcabc"), std::vector<int>{}, e<int>(" ??abcabc"));

	ASSERT_PARSE_SUCCESS(Tra3, e<int>("abc???????"), false, e<int>("?"));
	ASSERT_PARSE_FAILURE(Tra3, e<int>("??abc???????"));
	ASSERT_PARSE_SUCCESS(Tra3, e<int>("abc??abc???????"), false, e<int>("abc???????"));
	ASSERT_PARSE_SUCCESS(Tra3, e<int>("abc ??abc???????"), true, e<int>(" ??abc???????"));
	ASSERT_PARSE_FAILURE(Tra3, e<int>(""));

	ASSERT_PARSE_SUCCESS(Tra4, e<int>("abcabcabcabc??"), 36, e<int>(""));
	ASSERT_PARSE_SUCCESS(Tra4, e<int>("abcabcabcabc"), 12, e<int>(""));
	ASSERT_PARSE_SUCCESS(Tra4, e<int>("abcabcabcabc ??"), 12, e<int>(" ??"));
	ASSERT_PARSE_SUCCESS(Tra4, e<int>("abc"), 3, e<int>(""));
	ASSERT_PARSE_FAILURE(Tra4, e<int>(" abc"));
	ASSERT_PARSE_FAILURE(Tra4, e<int>(""));
}

TEST("Transform", "Move only")
{
	{
		using T = MoveOnlyWrapper<Output<char>>;
		using P = Transform<ABC, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
		ASSERT_PARSE_FAILURE(P, "dcba");
		ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
	}

	{
		using T = MoveOnlyWrapper<Output<wchar_t>>;
		using P = Transform<ABC, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
		ASSERT_PARSE_FAILURE(P, L"dcba");
		ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
	}

	{
		using T = MoveOnlyWrapper<Output<int>>;
		using P = Transform<ABC, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, e<int>("abcd"), T(e<int>("abc")), e<int>("d"));
		ASSERT_PARSE_FAILURE(P, e<int>("dcba"));
		ASSERT_PARSE_SUCCESS(P, e<int>("abcabcd"), T(e<int>("abc")), e<int>("abcd"));
	}
}

TEST("Transform", "Copy only")
{
	{
		using T = CopyOnlyWrapper<Output<char>>;
		using P = Transform<ABC, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
		ASSERT_PARSE_FAILURE(P, "dcba");
		ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
	}

	{
		using T = CopyOnlyWrapper<Output<wchar_t>>;
		using P = Transform<ABC, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
		ASSERT_PARSE_FAILURE(P, L"dcba");
		ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
	}

	{
		using T = CopyOnlyWrapper<Output<int>>;
		using P = Transform<ABC, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, e<int>("abcd"), T(e<int>("abc")), e<int>("d"));
		ASSERT_PARSE_FAILURE(P, e<int>("dcba"));
		ASSERT_PARSE_SUCCESS(P, e<int>("abcabcd"), T(e<int>("abc")), e<int>("abcd"));
	}
}
