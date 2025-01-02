// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("filter_parser");

TEST("filter_parser", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Fil1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Fil2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Fil3, value_type);

#if defined(VALUE_TYPE_CHAR)
	ASSERT_IS_PARSER(Fil1, char, filter_family, std::vector<output_span<char>>);
#elif defined(VALUE_TYPE_WCHAR_T)
	ASSERT_IS_NOT_PARSER(Fil1, char, filter_family);
#else
#error
#endif
	ASSERT_IS_PARSER(Fil2, char, filter_family, std::optional<output_span<char>>);
	ASSERT_IS_PARSER(Fil3, char, filter_family, std::tuple<output_span<char>, std::vector<output_span<char>>>);

#if defined(VALUE_TYPE_CHAR)
	ASSERT_IS_NOT_PARSER(Fil1, wchar_t, filter_family);
#elif defined(VALUE_TYPE_WCHAR_T)
	ASSERT_IS_PARSER(Fil1, wchar_t, filter_family, std::vector<output_span<wchar_t>>);
#else
#error
#endif
	ASSERT_IS_PARSER(Fil2, wchar_t, filter_family, std::optional<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Fil3, wchar_t, filter_family, std::tuple<output_span<wchar_t>, std::vector<output_span<wchar_t>>>);

	ASSERT_IS_NOT_PARSER(Fil1, int, filter_family);
	ASSERT_IS_PARSER(Fil2, int, filter_family, std::optional<output_span<int>>);
	ASSERT_IS_PARSER(Fil3, int, filter_family, std::tuple<output_span<int>, std::vector<output_span<int>>>);
}

TEST("filter_parser", "Parse all")
{
    {
        using vec_type = std::vector<output_span<::value_type>>;
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil1, TT("abcabcabcabcabcab"), TT("ab"));
        ASSERT_PARSE_SUCCESS(Fil1, TT("abcabcabcabcab"), vec_type({ TT("abc"), TT("abc"), TT("abc"), TT("abc") }), TT("ab"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil1, TT("abcabcabcab"), TT("ab"));
        ASSERT_PARSE_SUCCESS(Fil1, TT("abcabcab"), vec_type({ TT("abc"), TT("abc") }), TT("ab"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil1, TT("abc"), TT(""));
        ASSERT_PARSE_FAILURE(Fil1, TT("ab"));
        ASSERT_PARSE_FAILURE(Fil1, TT(""));
    }

    {
        using opt_type = std::optional<output_span<char>>;
        ASSERT_PARSE_SUCCESS(Fil2, "abcabc", opt_type("abc"), "abc");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil2, "a??bcabc", "a??bcabc");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil2, "", "");
        ASSERT_PARSE_SUCCESS(Fil2, "??abcabc", opt_type("??"), "abcabc");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil2, " ??abcabc", " ??abcabc");
    }

	{
		using vec_type = std::vector<output_span<char>>;
		using tuple_type = std::tuple<output_span<char>, vec_type>;
		ASSERT_PARSE_SUCCESS(Fil3, "abcabc", tuple_type("abc", {}), "abc");
		ASSERT_PARSE_SUCCESS(Fil3, "abc", tuple_type("abc", {}), "");
		ASSERT_PARSE_SUCCESS(Fil3, "abc?", tuple_type("abc", {}), "?");
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, "abc??", "");
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, "abc???", "?");
		ASSERT_PARSE_SUCCESS(Fil3, "abc????", tuple_type("abc", { "??", "??" }), "");
		ASSERT_PARSE_SUCCESS(Fil3, "abc?????", tuple_type("abc", { "??", "??" }), "?");
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, "abc??????", "");
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, "abc???????", "?");
		ASSERT_PARSE_SUCCESS(Fil3, "abc????????", tuple_type("abc", { "??", "??", "??", "??" }), "");
		ASSERT_PARSE_SUCCESS(Fil3, "abc?????????", tuple_type("abc", { "??", "??", "??", "??" }), "?");
		ASSERT_PARSE_FAILURE(Fil3, "??abc???????");
		ASSERT_PARSE_FAILURE(Fil3, "");
	}

    {
        using opt_type = std::optional<output_span<wchar_t>>;
        ASSERT_PARSE_SUCCESS(Fil2, L"abcabc", opt_type(L"abc"), L"abc");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil2, L"a??bcabc", L"a??bcabc");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil2, L"", L"");
        ASSERT_PARSE_SUCCESS(Fil2, L"??abcabc", opt_type(L"??"), L"abcabc");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil2, L" ??abcabc", L" ??abcabc");
    }

	{
		using vec_type = std::vector<output_span<wchar_t>>;
		using tuple_type = std::tuple<output_span<wchar_t>, vec_type>;
		ASSERT_PARSE_SUCCESS(Fil3, L"abcabc", tuple_type(L"abc", {}), L"abc");
		ASSERT_PARSE_SUCCESS(Fil3, L"abc", tuple_type(L"abc", {}), L"");
		ASSERT_PARSE_SUCCESS(Fil3, L"abc?", tuple_type(L"abc", {}), L"?");
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, L"abc??", L"");
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, L"abc???", L"?");
		ASSERT_PARSE_SUCCESS(Fil3, L"abc????", tuple_type(L"abc", { L"??", L"??" }), L"");
		ASSERT_PARSE_SUCCESS(Fil3, L"abc?????", tuple_type(L"abc", { L"??", L"??" }), L"?");
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, L"abc??????", L"");
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, L"abc???????", L"?");
		ASSERT_PARSE_SUCCESS(Fil3, L"abc????????", tuple_type(L"abc", { L"??", L"??", L"??", L"??" }), L"");
		ASSERT_PARSE_SUCCESS(Fil3, L"abc?????????", tuple_type(L"abc", { L"??", L"??", L"??", L"??" }), L"?");
		ASSERT_PARSE_FAILURE(Fil3, L"??abc???????");
		ASSERT_PARSE_FAILURE(Fil3, L"");
	}

    {
        using opt_type = std::optional<output_span<int>>;
        ASSERT_PARSE_SUCCESS(Fil2, e<int>("abcabc"), opt_type(e<int>("abc")), e<int>("abc"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil2, e<int>("a??bcabc"), e<int>("a??bcabc"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil2, e<int>(""), e<int>(""));
        ASSERT_PARSE_SUCCESS(Fil2, e<int>("??abcabc"), opt_type(e<int>("??")), e<int>("abcabc"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Fil2, e<int>(" ??abcabc"), e<int>(" ??abcabc"));
    }

	{
		using vec_type = std::vector<output_span<int>>;
		using tuple_type = std::tuple<output_span<int>, vec_type>;
		ASSERT_PARSE_SUCCESS(Fil3, e<int>("abcabc"), tuple_type(e<int>("abc"), {}), e<int>("abc"));
		ASSERT_PARSE_SUCCESS(Fil3, e<int>("abc"), tuple_type(e<int>("abc"), {}), e<int>(""));
		ASSERT_PARSE_SUCCESS(Fil3, e<int>("abc?"), tuple_type(e<int>("abc"), {}), e<int>("?"));
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, e<int>("abc??"), e<int>(""));
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, e<int>("abc???"), e<int>("?"));
		ASSERT_PARSE_SUCCESS(Fil3, e<int>("abc????"), tuple_type(e<int>("abc"), { e<int>("??"), e<int>("??") }), e<int>(""));
		ASSERT_PARSE_SUCCESS(Fil3, e<int>("abc?????"), tuple_type(e<int>("abc"), { e<int>("??"), e<int>("??") }), e<int>("?"));
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, e<int>("abc??????"), e<int>(""));
		ASSERT_PARSE_LOOKAHEAD_ONLY(Fil3, e<int>("abc???????"), e<int>("?"));
		ASSERT_PARSE_SUCCESS(Fil3, e<int>("abc????????"), tuple_type(e<int>("abc"), { e<int>("??"), e<int>("??"), e<int>("??"), e<int>("??") }), e<int>(""));
		ASSERT_PARSE_SUCCESS(Fil3, e<int>("abc?????????"), tuple_type(e<int>("abc"), { e<int>("??"), e<int>("??"), e<int>("??"), e<int>("??") }), e<int>("?"));
		ASSERT_PARSE_FAILURE(Fil3, e<int>("??abc???????"));
		ASSERT_PARSE_FAILURE(Fil3, e<int>(""));
	}
}

TEST("filter_parser", "void input")
{
	using P = ignore_parser<ABC>;

	constexpr auto func_good = []() { return true; };
	using FilterGood = filter_parser<P, integral_constant<func_good>>;
	ASSERT_IS_PARSER(FilterGood, value_type, filter_family, void);
	ASSERT_PARSE_SUCCESS_VOID(FilterGood, TT("abcd"), TT("d"));
	ASSERT_PARSE_FAILURE(FilterGood, TT(" abcd"));

	constexpr auto func_bad = [](auto) { return true; };
	using FilterBad = filter_parser<P, integral_constant<func_bad>>;
	ASSERT_IS_NOT_PARSER(FilterBad, value_type, filter_family);
}
