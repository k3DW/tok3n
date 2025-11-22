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
        EXPECT_THAT(the_parser<Fil1> | SUCCEEDS_LOOKAHEAD_ONLY(TT("abcabcabcabcabcab"), TT("ab")));
        EXPECT_THAT(the_parser<Fil1> | SUCCEEDS_PARSING(TT("abcabcabcabcab"), vec_type({ TT("abc"), TT("abc"), TT("abc"), TT("abc") }), TT("ab")));
        EXPECT_THAT(the_parser<Fil1> | SUCCEEDS_LOOKAHEAD_ONLY(TT("abcabcabcab"), TT("ab")));
        EXPECT_THAT(the_parser<Fil1> | SUCCEEDS_PARSING(TT("abcabcab"), vec_type({ TT("abc"), TT("abc") }), TT("ab")));
        EXPECT_THAT(the_parser<Fil1> | SUCCEEDS_LOOKAHEAD_ONLY(TT("abc"), TT("")));
        EXPECT_THAT(the_parser<Fil1> | FAILS_PARSING(TT("ab")));
        EXPECT_THAT(the_parser<Fil1> | FAILS_PARSING(TT("")));
    }

    {
        using opt_type = std::optional<output_span<char>>;
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_PARSING("abcabc", opt_type("abc"), "abc"));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_LOOKAHEAD_ONLY("a??bcabc", "a??bcabc"));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_LOOKAHEAD_ONLY("", ""));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_PARSING("??abcabc", opt_type("??"), "abcabc"));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_LOOKAHEAD_ONLY(" ??abcabc", " ??abcabc"));
    }

    {
        using vec_type = std::vector<output_span<char>>;
        using tuple_type = std::tuple<output_span<char>, vec_type>;
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING("abcabc", tuple_type("abc", {}), "abc"));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING("abc", tuple_type("abc", {}), ""));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING("abc?", tuple_type("abc", {}), "?"));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY("abc??", ""));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY("abc???", "?"));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING("abc????", tuple_type("abc", { "??", "??" }), ""));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING("abc?????", tuple_type("abc", { "??", "??" }), "?"));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY("abc??????", ""));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY("abc???????", "?"));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING("abc????????", tuple_type("abc", { "??", "??", "??", "??" }), ""));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING("abc?????????", tuple_type("abc", { "??", "??", "??", "??" }), "?"));
        EXPECT_THAT(the_parser<Fil3> | FAILS_PARSING("??abc???????"));
        EXPECT_THAT(the_parser<Fil3> | FAILS_PARSING(""));
    }

    {
        using opt_type = std::optional<output_span<wchar_t>>;
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_PARSING(L"abcabc", opt_type(L"abc"), L"abc"));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_LOOKAHEAD_ONLY(L"a??bcabc", L"a??bcabc"));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_LOOKAHEAD_ONLY(L"", L""));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_PARSING(L"??abcabc", opt_type(L"??"), L"abcabc"));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_LOOKAHEAD_ONLY(L" ??abcabc", L" ??abcabc"));
    }

    {
        using vec_type = std::vector<output_span<wchar_t>>;
        using tuple_type = std::tuple<output_span<wchar_t>, vec_type>;
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(L"abcabc", tuple_type(L"abc", {}), L"abc"));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(L"abc", tuple_type(L"abc", {}), L""));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(L"abc?", tuple_type(L"abc", {}), L"?"));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY(L"abc??", L""));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY(L"abc???", L"?"));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(L"abc????", tuple_type(L"abc", { L"??", L"??" }), L""));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(L"abc?????", tuple_type(L"abc", { L"??", L"??" }), L"?"));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY(L"abc??????", L""));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY(L"abc???????", L"?"));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(L"abc????????", tuple_type(L"abc", { L"??", L"??", L"??", L"??" }), L""));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(L"abc?????????", tuple_type(L"abc", { L"??", L"??", L"??", L"??" }), L"?"));
        EXPECT_THAT(the_parser<Fil3> | FAILS_PARSING(L"??abc???????"));
        EXPECT_THAT(the_parser<Fil3> | FAILS_PARSING(L""));
    }

    static constexpr auto arr_abc = e<int>("abc");
    static constexpr auto arr_qq = e<int>("??");

    {
        using opt_type = std::optional<output_span<int>>;
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_PARSING(e<int>("abcabc"), opt_type(arr_abc), e<int>("abc")));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_LOOKAHEAD_ONLY(e<int>("a??bcabc"), e<int>("a??bcabc")));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_LOOKAHEAD_ONLY(e<int>(""), e<int>("")));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_PARSING(e<int>("??abcabc"), opt_type(arr_qq), e<int>("abcabc")));
        EXPECT_THAT(the_parser<Fil2> | SUCCEEDS_LOOKAHEAD_ONLY(e<int>(" ??abcabc"), e<int>(" ??abcabc")));
    }

    {
        using vec_type = std::vector<output_span<int>>;
        using tuple_type = std::tuple<output_span<int>, vec_type>;
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(e<int>("abcabc"), tuple_type(arr_abc, {}), e<int>("abc")));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(e<int>("abc"), tuple_type(arr_abc, {}), e<int>("")));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(e<int>("abc?"), tuple_type(arr_abc, {}), e<int>("?")));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY(e<int>("abc??"), e<int>("")));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY(e<int>("abc???"), e<int>("?")));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(e<int>("abc????"), tuple_type(arr_abc, { arr_qq, arr_qq }), e<int>("")));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(e<int>("abc?????"), tuple_type(arr_abc, { arr_qq, arr_qq }), e<int>("?")));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY(e<int>("abc??????"), e<int>("")));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_LOOKAHEAD_ONLY(e<int>("abc???????"), e<int>("?")));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(e<int>("abc????????"), tuple_type(arr_abc, { arr_qq, arr_qq, arr_qq, arr_qq }), e<int>("")));
        EXPECT_THAT(the_parser<Fil3> | SUCCEEDS_PARSING(e<int>("abc?????????"), tuple_type(arr_abc, { arr_qq, arr_qq, arr_qq, arr_qq }), e<int>("?")));
        EXPECT_THAT(the_parser<Fil3> | FAILS_PARSING(e<int>("??abc???????")));
        EXPECT_THAT(the_parser<Fil3> | FAILS_PARSING(e<int>("")));
    }
}

TEST("filter_parser", "void input")
{
    using P = ignore_parser<ABC>;

    constexpr auto func_good = []() { return true; };
    using FilterGood = filter_parser<P, integral_constant<func_good>>;
    EXPECT_THAT(the_parser<FilterGood> | has_family<filter_family>);
    EXPECT_THAT(the_parser<FilterGood> | is_parser_for<value_type>.with_result<void>);
    EXPECT_THAT(the_parser<FilterGood> | SUCCEEDS_PARSING_VOID(TT("abcd"), TT("d")));
    EXPECT_THAT(the_parser<FilterGood> | FAILS_PARSING(TT(" abcd")));

    constexpr auto func_bad = [](auto) { return true; };
    using FilterBad = filter_parser<P, integral_constant<func_bad>>;
    EXPECT_THAT(the_parser<FilterBad> | has_family<filter_family>);
    EXPECT_THAT(the_parser<FilterBad> | is_not_parser_for<value_type>);
}

} // namespace
} // namespace k3::tok3n::tests
