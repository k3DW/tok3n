#include "samples.h"

FIXTURE("Map");

TEST("Map", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Map1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Map2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Map3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Map4, value_type);

#if defined(VALUE_TYPE_CHAR)
	ASSERT_IS_PARSER(Map1, char, MapFamily, std::size_t);
#elif defined(VALUE_TYPE_WCHAR_T)
	ASSERT_IS_NOT_PARSER(Map1, char, MapFamily);
#else
#error
#endif
	ASSERT_IS_PARSER(Map2, char, MapFamily, std::vector<char>);
	ASSERT_IS_PARSER(Map3, char, MapFamily, bool);
	ASSERT_IS_PARSER(Map4, char, MapFamily, std::size_t);

#if defined(VALUE_TYPE_CHAR)
	ASSERT_IS_NOT_PARSER(Map1, wchar_t, MapFamily);
#elif defined(VALUE_TYPE_WCHAR_T)
	ASSERT_IS_PARSER(Map1, wchar_t, MapFamily, std::size_t);
#else
#error
#endif
	ASSERT_IS_PARSER(Map2, wchar_t, MapFamily, std::vector<wchar_t>);
	ASSERT_IS_PARSER(Map3, wchar_t, MapFamily, bool);
	ASSERT_IS_PARSER(Map4, wchar_t, MapFamily, std::size_t);

	ASSERT_IS_NOT_PARSER(Map1, int, MapFamily);
	ASSERT_IS_PARSER(Map2, int, MapFamily, std::vector<int>);
	ASSERT_IS_PARSER(Map3, int, MapFamily, bool);
	ASSERT_IS_PARSER(Map4, int, MapFamily, std::size_t);
}

TEST("Map", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Map1, TT("abcabcabcab"), 3, TT("ab"));
	ASSERT_PARSE_FAILURE(Map1, TT(""));
	ASSERT_PARSE_FAILURE(Map1, TT("ab"));
	ASSERT_PARSE_SUCCESS(Map1, TT("abc"), 1, TT(""));
		
	ASSERT_PARSE_SUCCESS(Map2, "abcabc", std::vector<char>({ 'a', 'b', 'c' }), "abc");
	ASSERT_PARSE_SUCCESS(Map2, "a??bcabc", std::vector<char>{}, "a??bcabc");
	ASSERT_PARSE_SUCCESS(Map2, "", std::vector<char>{}, "");
	ASSERT_PARSE_SUCCESS(Map2, "??abcabc", std::vector<char>({ '?', '?' }), "abcabc");
	ASSERT_PARSE_SUCCESS(Map2, " ??abcabc", std::vector<char>{}, " ??abcabc");
		
	ASSERT_PARSE_SUCCESS(Map3, "abc???????", false, "?");
	ASSERT_PARSE_FAILURE(Map3, "??abc???????");
	ASSERT_PARSE_SUCCESS(Map3, "abc??abc???????", false, "abc???????");
	ASSERT_PARSE_SUCCESS(Map3, "abc ??abc???????", true, " ??abc???????");
	ASSERT_PARSE_FAILURE(Map3, "");
		
	ASSERT_PARSE_SUCCESS(Map4, "abcabcabcabc??", 36, "");
	ASSERT_PARSE_SUCCESS(Map4, "abcabcabcabc", 12, "");
	ASSERT_PARSE_SUCCESS(Map4, "abcabcabcabc ??", 12, " ??");
	ASSERT_PARSE_SUCCESS(Map4, "abc", 3, "");
	ASSERT_PARSE_FAILURE(Map4, " abc");
	ASSERT_PARSE_FAILURE(Map4, "");
		
	ASSERT_PARSE_SUCCESS(Map2, L"abcabc", std::vector<wchar_t>({ 'a', 'b', 'c' }), L"abc");
	ASSERT_PARSE_SUCCESS(Map2, L"a??bcabc", std::vector<wchar_t>{}, L"a??bcabc");
	ASSERT_PARSE_SUCCESS(Map2, L"", std::vector<wchar_t>{}, L"");
	ASSERT_PARSE_SUCCESS(Map2, L"??abcabc", std::vector<wchar_t>({ '?', '?' }), L"abcabc");
	ASSERT_PARSE_SUCCESS(Map2, L" ??abcabc", std::vector<wchar_t>{}, L" ??abcabc");
		
	ASSERT_PARSE_SUCCESS(Map3, L"abc???????", false, L"?");
	ASSERT_PARSE_FAILURE(Map3, L"??abc???????");
	ASSERT_PARSE_SUCCESS(Map3, L"abc??abc???????", false, L"abc???????");
	ASSERT_PARSE_SUCCESS(Map3, L"abc ??abc???????", true, L" ??abc???????");
	ASSERT_PARSE_FAILURE(Map3, L"");
		
	ASSERT_PARSE_SUCCESS(Map4, L"abcabcabcabc??", 36, L"");
	ASSERT_PARSE_SUCCESS(Map4, L"abcabcabcabc", 12, L"");
	ASSERT_PARSE_SUCCESS(Map4, L"abcabcabcabc ??", 12, L" ??");
	ASSERT_PARSE_SUCCESS(Map4, L"abc", 3, L"");
	ASSERT_PARSE_FAILURE(Map4, L" abc");
	ASSERT_PARSE_FAILURE(Map4, L"");
		
	ASSERT_PARSE_SUCCESS(Map2, e<int>("abcabc"), std::vector<int>({ 'a', 'b', 'c' }), e<int>("abc"));
	ASSERT_PARSE_SUCCESS(Map2, e<int>("a??bcabc"), std::vector<int>{}, e<int>("a??bcabc"));
	ASSERT_PARSE_SUCCESS(Map2, e<int>(""), std::vector<int>{}, e<int>(""));
	ASSERT_PARSE_SUCCESS(Map2, e<int>("??abcabc"), std::vector<int>({ '?', '?' }), e<int>("abcabc"));
	ASSERT_PARSE_SUCCESS(Map2, e<int>(" ??abcabc"), std::vector<int>{}, e<int>(" ??abcabc"));
		
	ASSERT_PARSE_SUCCESS(Map3, e<int>("abc???????"), false, e<int>("?"));
	ASSERT_PARSE_FAILURE(Map3, e<int>("??abc???????"));
	ASSERT_PARSE_SUCCESS(Map3, e<int>("abc??abc???????"), false, e<int>("abc???????"));
	ASSERT_PARSE_SUCCESS(Map3, e<int>("abc ??abc???????"), true, e<int>(" ??abc???????"));
	ASSERT_PARSE_FAILURE(Map3, e<int>(""));
		
	ASSERT_PARSE_SUCCESS(Map4, e<int>("abcabcabcabc??"), 36, e<int>(""));
	ASSERT_PARSE_SUCCESS(Map4, e<int>("abcabcabcabc"), 12, e<int>(""));
	ASSERT_PARSE_SUCCESS(Map4, e<int>("abcabcabcabc ??"), 12, e<int>(" ??"));
	ASSERT_PARSE_SUCCESS(Map4, e<int>("abc"), 3, e<int>(""));
	ASSERT_PARSE_FAILURE(Map4, e<int>(" abc"));
	ASSERT_PARSE_FAILURE(Map4, e<int>(""));
}

TEST("Map", "Move only")
{
	{
		using T = MoveOnlyWrapper<Output<char>>;
		using P = Map<ABC, detail::integral_constant<T::make>>;
		ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
		ASSERT_PARSE_FAILURE(P, "dcba");
		ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
	}

	{
		using T = MoveOnlyWrapper<Output<wchar_t>>;
		using P = Map<ABC, detail::integral_constant<T::make>>;
		ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
		ASSERT_PARSE_FAILURE(P, L"dcba");
		ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
	}

	{
		using T = MoveOnlyWrapper<Output<int>>;
		using P = Map<ABC, detail::integral_constant<T::make>>;
		ASSERT_PARSE_SUCCESS(P, e<int>("abcd"), T(e<int>("abc")), e<int>("d"));
		ASSERT_PARSE_FAILURE(P, e<int>("dcba"));
		ASSERT_PARSE_SUCCESS(P, e<int>("abcabcd"), T(e<int>("abc")), e<int>("abcd"));
	}
}

TEST("Map", "Copy only")
{
	{
		using T = CopyOnlyWrapper<Output<char>>;
		using P = Map<ABC, detail::integral_constant<T::make>>;
		ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
		ASSERT_PARSE_FAILURE(P, "dcba");
		ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
	}

	{
		using T = CopyOnlyWrapper<Output<wchar_t>>;
		using P = Map<ABC, detail::integral_constant<T::make>>;
		ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
		ASSERT_PARSE_FAILURE(P, L"dcba");
		ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
	}

	{
		using T = CopyOnlyWrapper<Output<int>>;
		using P = Map<ABC, detail::integral_constant<T::make>>;
		ASSERT_PARSE_SUCCESS(P, e<int>("abcd"), T(e<int>("abc")), e<int>("d"));
		ASSERT_PARSE_FAILURE(P, e<int>("dcba"));
		ASSERT_PARSE_SUCCESS(P, e<int>("abcabcd"), T(e<int>("abc")), e<int>("abcd"));
	}
}

TEST("Map", "void input")
{
	using P = Ignore<ABC>;

	constexpr auto func_good = []() { return 0; };
	using MapGood = Map<P, detail::integral_constant<func_good>>;
	ASSERT_IS_PARSER(MapGood, value_type, MapFamily, int);
	ASSERT_PARSE_SUCCESS(MapGood, "abcd", 0, "d");
	ASSERT_PARSE_FAILURE(MapGood, " abcd");

	constexpr auto func_bad = [](auto) { return 0; };
	using MapBad = Map<P, detail::integral_constant<func_bad>>;
	ASSERT_IS_NOT_PARSER(MapBad, value_type, MapFamily);
}

TEST("Map", "void output")
{
	using P = ABC;

	constexpr auto func_good = [](auto) {};
	using MapGood = Map<P, detail::integral_constant<func_good>>;
	ASSERT_IS_PARSER(MapGood, value_type, MapFamily, void);
	ASSERT_PARSE_SUCCESS_VOID(MapGood, "abcd", "d");
	ASSERT_PARSE_FAILURE(MapGood, " abcd");

	constexpr auto func_bad = []() {};
	using MapBad = Map<P, detail::integral_constant<func_bad>>;
	ASSERT_IS_NOT_PARSER(MapBad, value_type, MapFamily);
}

TEST("Map", "void input and void output")
{
	using P = Ignore<ABC>;

	constexpr auto func_good = []() {};
	using MapGood = Map<P, detail::integral_constant<func_good>>;
	ASSERT_IS_PARSER(MapGood, value_type, MapFamily, void);
	ASSERT_PARSE_SUCCESS_VOID(MapGood, "abcd", "d");
	ASSERT_PARSE_FAILURE(MapGood, " abcd");

	constexpr auto func_bad = [](auto) {};
	using MapBad = Map<P, detail::integral_constant<func_bad>>;
	ASSERT_IS_NOT_PARSER(MapBad, value_type, MapFamily);
}
