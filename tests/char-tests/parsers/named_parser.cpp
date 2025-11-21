// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("named_parser");

TEST("named_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Nam1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Nam2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Nam3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Nam4> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Nam1> | has_family<named_family>);
    EXPECT_THAT(the_parser<Nam2> | has_family<named_family>);
    EXPECT_THAT(the_parser<Nam3> | has_family<named_family>);
    EXPECT_THAT(the_parser<Nam4> | has_family<named_family>);

    EXPECT_THAT(the_parser<Nam1> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Nam2> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Nam3> | is_parser_for<char>.with_result<std::optional<output_span<char>>>);
    EXPECT_THAT(the_parser<Nam4> | (is_parser_for<char>.with_result<std::tuple<output_span<char>, std::vector<output_span<char>>>>));

    EXPECT_THAT(the_parser<Nam1> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Nam2> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Nam3> | is_parser_for<wchar_t>.with_result<std::optional<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Nam4> | (is_parser_for<wchar_t>.with_result<std::tuple<output_span<wchar_t>, std::vector<output_span<wchar_t>>>>));

    EXPECT_THAT(the_parser<Nam1> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Nam2> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Nam3> | is_parser_for<int>.with_result<std::optional<output_span<int>>>);
    EXPECT_THAT(the_parser<Nam4> | (is_parser_for<int>.with_result<std::tuple<output_span<int>, std::vector<output_span<int>>>>));
}

TEST("named_parser", "named_parser<all_of_parser>")
{
    EXPECT_THAT(the_parser<Nam1> | SUCCEEDS_PARSING("abc", "abc", ""));
    EXPECT_THAT(the_parser<Nam1> | SUCCEEDS_PARSING("abcd", "abc", "d"));
    ASSERT_PARSE_FAILURE(Nam1, " abc");

    EXPECT_THAT(the_parser<Nam1> | SUCCEEDS_PARSING(L"abc", L"abc", L""));
    EXPECT_THAT(the_parser<Nam1> | SUCCEEDS_PARSING(L"abcd", L"abc", L"d"));
    ASSERT_PARSE_FAILURE(Nam1, L" abc");

    EXPECT_THAT(the_parser<Nam1> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("abc"), e<int>("")));
    EXPECT_THAT(the_parser<Nam1> | SUCCEEDS_PARSING(e<int>("abcd"), e<int>("abc"), e<int>("d")));
    ASSERT_PARSE_FAILURE(Nam1, e<int>(" abc"));
}

TEST("named_parser", "named_parser<one_or_more_parser>")
{
    {
        using type = std::vector<output_span<char>>;
        EXPECT_THAT(the_parser<Nam2> | SUCCEEDS_PARSING("abcabcab", (type{"abc", "abc"}), "ab"));
        EXPECT_THAT(the_parser<Nam2> | SUCCEEDS_PARSING("abcd", (type{"abc"}), "d"));
        EXPECT_THAT(the_parser<Nam2> | SUCCEEDS_PARSING("abc abc", (type{"abc"}), " abc"));
        ASSERT_PARSE_FAILURE(Nam2, "ab abc");
        ASSERT_PARSE_FAILURE(Nam2, " ab abc");
    }

    {
        using type = std::vector<output_span<wchar_t>>;
        EXPECT_THAT(the_parser<Nam2> | SUCCEEDS_PARSING(L"abcabcab", (type{L"abc", L"abc"}), L"ab"));
        EXPECT_THAT(the_parser<Nam2> | SUCCEEDS_PARSING(L"abcd", (type{L"abc"}), L"d"));
        EXPECT_THAT(the_parser<Nam2> | SUCCEEDS_PARSING(L"abc abc", (type{L"abc"}), L" abc"));
        ASSERT_PARSE_FAILURE(Nam2, L"ab abc");
        ASSERT_PARSE_FAILURE(Nam2, L" ab abc");
    }

    {
        using type = std::vector<output_span<int>>;
        static constexpr auto arr_abc = e<int>("abc");
        EXPECT_THAT(the_parser<Nam2> | SUCCEEDS_PARSING(e<int>("abcabcab"), (type{arr_abc, arr_abc}), e<int>("ab")));
        EXPECT_THAT(the_parser<Nam2> | SUCCEEDS_PARSING(e<int>("abcd"), (type{arr_abc}), e<int>("d")));
        EXPECT_THAT(the_parser<Nam2> | SUCCEEDS_PARSING(e<int>("abc abc"), (type{arr_abc}), e<int>(" abc")));
        ASSERT_PARSE_FAILURE(Nam2, e<int>("ab abc"));
        ASSERT_PARSE_FAILURE(Nam2, e<int>(" ab abc"));
    }
}

TEST("named_parser", "named_parser<maybe_parser>")
{
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING("abcabcab", "abc", "abcab"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING("abcd", "abc", "d"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING("abc abc", "abc", " abc"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING("ab abc", std::nullopt, "ab abc"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(" ab abc", std::nullopt, " ab abc"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING("?? ab abc", "??", " ab abc"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING("??? ab abc", "??", "? ab abc"));

    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(L"abcabcab", L"abc", L"abcab"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(L"abcd", L"abc", L"d"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(L"abc abc", L"abc", L" abc"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(L"ab abc", std::nullopt, L"ab abc"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(L" ab abc", std::nullopt, L" ab abc"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(L"?? ab abc", L"??", L" ab abc"));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(L"??? ab abc", L"??", L"? ab abc"));

    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(e<int>("abcabcab"), e<int>("abc"), e<int>("abcab")));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(e<int>("abcd"), e<int>("abc"), e<int>("d")));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(e<int>("abc abc"), e<int>("abc"), e<int>(" abc")));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(e<int>("ab abc"), std::nullopt, e<int>("ab abc")));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(e<int>(" ab abc"), std::nullopt, e<int>(" ab abc")));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(e<int>("?? ab abc"), e<int>("??"), e<int>(" ab abc")));
    EXPECT_THAT(the_parser<Nam3> | SUCCEEDS_PARSING(e<int>("??? ab abc"), e<int>("??"), e<int>("? ab abc")));
}

TEST("named_parser", "named_parser<sequence_parser>")
{
    {
        using type = std::tuple<output_span<char>, std::vector<output_span<char>>>;
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING("abcabcab", (type{"abc", {}}), "abcab"));
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING("abc?d", (type{"abc", {}}), "?d"));
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING("abc???? abc", (type{"abc", {"??", "??"}}), " abc"));
        ASSERT_PARSE_FAILURE(Nam4, "ab???? abc");
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING("abc?? ?? abc", (type{"abc", {"??"}}), " ?? abc"));
    }

    {
        using type = std::tuple<output_span<wchar_t>, std::vector<output_span<wchar_t>>>;
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING(L"abcabcab", (type{L"abc", {}}), L"abcab"));
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING(L"abc?d", (type{L"abc", {}}), L"?d"));
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING(L"abc???? abc", (type{L"abc", {L"??", L"??"}}), L" abc"));
        ASSERT_PARSE_FAILURE(Nam4, L"ab???? abc");
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING(L"abc?? ?? abc", (type{L"abc", {L"??"}}), L" ?? abc"));
    }

    {
        using type = std::tuple<output_span<int>, std::vector<output_span<int>>>;
        static constexpr auto arr_abc = e<int>("abc");
        static constexpr auto arr_qq = e<int>("??");
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING(e<int>("abcabcab"), (type{arr_abc, {}}), e<int>("abcab")));
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING(e<int>("abc?d"), (type{arr_abc, {}}), e<int>("?d")));
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING(e<int>("abc???? abc"), (type{arr_abc, {arr_qq, arr_qq}}), e<int>(" abc")));
        ASSERT_PARSE_FAILURE(Nam4, e<int>("ab???? abc"));
        EXPECT_THAT(the_parser<Nam4> | SUCCEEDS_PARSING(e<int>("abc?? ?? abc"), (type{arr_abc, {arr_qq}}), e<int>(" ?? abc")));
    }
}

} // namespace
} // namespace k3::tok3n::tests
