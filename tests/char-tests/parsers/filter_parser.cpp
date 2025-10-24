// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("filter_parser");

TEST("filter_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Fil1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Fil2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Fil3> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Fil1> | has_family<filter_family>);
    EXPECT_THAT(the_parser<Fil2> | has_family<filter_family>);
    EXPECT_THAT(the_parser<Fil3> | has_family<filter_family>);

#if defined(VALUE_TYPE_CHAR)
    EXPECT_THAT(the_parser<Fil1> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
#elif defined(VALUE_TYPE_WCHAR_T)
    EXPECT_THAT(the_parser<Fil1> | is_not_parser_for<char>);
#else
#error
#endif
    EXPECT_THAT(the_parser<Fil2> | is_parser_for<char>.with_result<std::optional<output_span<char>>>);
    EXPECT_THAT(the_parser<Fil3> | (is_parser_for<char>.with_result<std::tuple<output_span<char>, std::vector<output_span<char>>>>));

#if defined(VALUE_TYPE_CHAR)
    EXPECT_THAT(the_parser<Fil1> | is_not_parser_for<wchar_t>);
#elif defined(VALUE_TYPE_WCHAR_T)
    EXPECT_THAT(the_parser<Fil1> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
#else
#error
#endif
    EXPECT_THAT(the_parser<Fil2> | is_parser_for<wchar_t>.with_result<std::optional<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Fil3> | (is_parser_for<wchar_t>.with_result<std::tuple<output_span<wchar_t>, std::vector<output_span<wchar_t>>>>));

    EXPECT_THAT(the_parser<Fil1> | is_not_parser_for<int>);
    EXPECT_THAT(the_parser<Fil2> | is_parser_for<int>.with_result<std::optional<output_span<int>>>);
    EXPECT_THAT(the_parser<Fil3> | (is_parser_for<int>.with_result<std::tuple<output_span<int>, std::vector<output_span<int>>>>));
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
    EXPECT_THAT(the_parser<FilterGood> | has_family<filter_family>);
    EXPECT_THAT(the_parser<FilterGood> | is_parser_for<value_type>.with_result<void>);
    ASSERT_PARSE_SUCCESS_VOID(FilterGood, TT("abcd"), TT("d"));
    ASSERT_PARSE_FAILURE(FilterGood, TT(" abcd"));

    constexpr auto func_bad = [](auto) { return true; };
    using FilterBad = filter_parser<P, integral_constant<func_bad>>;
    EXPECT_THAT(the_parser<FilterBad> | has_family<filter_family>);
    EXPECT_THAT(the_parser<FilterBad> | is_not_parser_for<value_type>);
}

} // namespace
} // namespace k3::tok3n::tests
