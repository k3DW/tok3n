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
    ASSERT_PARSE_SUCCESS(Nam1, "abc", "abc", "");
    ASSERT_PARSE_SUCCESS(Nam1, "abcd", "abc", "d");
    ASSERT_PARSE_FAILURE(Nam1, " abc");

    ASSERT_PARSE_SUCCESS(Nam1, L"abc", L"abc", L"");
    ASSERT_PARSE_SUCCESS(Nam1, L"abcd", L"abc", L"d");
    ASSERT_PARSE_FAILURE(Nam1, L" abc");

    ASSERT_PARSE_SUCCESS(Nam1, e<int>("abc"), e<int>("abc"), e<int>(""));
    ASSERT_PARSE_SUCCESS(Nam1, e<int>("abcd"), e<int>("abc"), e<int>("d"));
    ASSERT_PARSE_FAILURE(Nam1, e<int>(" abc"));
}

TEST("named_parser", "named_parser<one_or_more_parser>")
{
    {
        using type = std::vector<output_span<char>>;
        ASSERT_PARSE_SUCCESS(Nam2, "abcabcab", (type{"abc", "abc"}), "ab");
        ASSERT_PARSE_SUCCESS(Nam2, "abcd", (type{"abc"}), "d");
        ASSERT_PARSE_SUCCESS(Nam2, "abc abc", (type{"abc"}), " abc");
        ASSERT_PARSE_FAILURE(Nam2, "ab abc");
        ASSERT_PARSE_FAILURE(Nam2, " ab abc");
    }

    {
        using type = std::vector<output_span<wchar_t>>;
        ASSERT_PARSE_SUCCESS(Nam2, L"abcabcab", (type{L"abc", L"abc"}), L"ab");
        ASSERT_PARSE_SUCCESS(Nam2, L"abcd", (type{L"abc"}), L"d");
        ASSERT_PARSE_SUCCESS(Nam2, L"abc abc", (type{L"abc"}), L" abc");
        ASSERT_PARSE_FAILURE(Nam2, L"ab abc");
        ASSERT_PARSE_FAILURE(Nam2, L" ab abc");
    }

    {
        using type = std::vector<output_span<int>>;
        ASSERT_PARSE_SUCCESS(Nam2, e<int>("abcabcab"), (type{e<int>("abc"), e<int>("abc")}), e<int>("ab"));
        ASSERT_PARSE_SUCCESS(Nam2, e<int>("abcd"), (type{e<int>("abc")}), e<int>("d"));
        ASSERT_PARSE_SUCCESS(Nam2, e<int>("abc abc"), (type{e<int>("abc")}), e<int>(" abc"));
        ASSERT_PARSE_FAILURE(Nam2, e<int>("ab abc"));
        ASSERT_PARSE_FAILURE(Nam2, e<int>(" ab abc"));
    }
}

TEST("named_parser", "named_parser<maybe_parser>")
{
    ASSERT_PARSE_SUCCESS(Nam3, "abcabcab", "abc", "abcab");
    ASSERT_PARSE_SUCCESS(Nam3, "abcd", "abc", "d");
    ASSERT_PARSE_SUCCESS(Nam3, "abc abc", "abc", " abc");
    ASSERT_PARSE_SUCCESS(Nam3, "ab abc", std::nullopt, "ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, " ab abc", std::nullopt, " ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, "?? ab abc", "??", " ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, "??? ab abc", "??", "? ab abc");

    ASSERT_PARSE_SUCCESS(Nam3, L"abcabcab", L"abc", L"abcab");
    ASSERT_PARSE_SUCCESS(Nam3, L"abcd", L"abc", L"d");
    ASSERT_PARSE_SUCCESS(Nam3, L"abc abc", L"abc", L" abc");
    ASSERT_PARSE_SUCCESS(Nam3, L"ab abc", std::nullopt, L"ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, L" ab abc", std::nullopt, L" ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, L"?? ab abc", L"??", L" ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, L"??? ab abc", L"??", L"? ab abc");

    ASSERT_PARSE_SUCCESS(Nam3, e<int>("abcabcab"), e<int>("abc"), e<int>("abcab"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>("abcd"), e<int>("abc"), e<int>("d"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>("abc abc"), e<int>("abc"), e<int>(" abc"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>("ab abc"), std::nullopt, e<int>("ab abc"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>(" ab abc"), std::nullopt, e<int>(" ab abc"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>("?? ab abc"), e<int>("??"), e<int>(" ab abc"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>("??? ab abc"), e<int>("??"), e<int>("? ab abc"));
}

TEST("named_parser", "named_parser<sequence_parser>")
{
    {
        using type = std::tuple<output_span<char>, std::vector<output_span<char>>>;
        ASSERT_PARSE_SUCCESS(Nam4, "abcabcab", (type{"abc", {}}), "abcab");
        ASSERT_PARSE_SUCCESS(Nam4, "abc?d", (type{"abc", {}}), "?d");
        ASSERT_PARSE_SUCCESS(Nam4, "abc???? abc", (type{"abc", {"??", "??"}}), " abc");
        ASSERT_PARSE_FAILURE(Nam4, "ab???? abc");
        ASSERT_PARSE_SUCCESS(Nam4, "abc?? ?? abc", (type{"abc", {"??"}}), " ?? abc");
    }

    {
        using type = std::tuple<output_span<wchar_t>, std::vector<output_span<wchar_t>>>;
        ASSERT_PARSE_SUCCESS(Nam4, L"abcabcab", (type{L"abc", {}}), L"abcab");
        ASSERT_PARSE_SUCCESS(Nam4, L"abc?d", (type{L"abc", {}}), L"?d");
        ASSERT_PARSE_SUCCESS(Nam4, L"abc???? abc", (type{L"abc", {L"??", L"??"}}), L" abc");
        ASSERT_PARSE_FAILURE(Nam4, L"ab???? abc");
        ASSERT_PARSE_SUCCESS(Nam4, L"abc?? ?? abc", (type{L"abc", {L"??"}}), L" ?? abc");
    }

    {
        using type = std::tuple<output_span<int>, std::vector<output_span<int>>>;
        ASSERT_PARSE_SUCCESS(Nam4, e<int>("abcabcab"), (type{e<int>("abc"), {}}), e<int>("abcab"));
        ASSERT_PARSE_SUCCESS(Nam4, e<int>("abc?d"), (type{e<int>("abc"), {}}), e<int>("?d"));
        ASSERT_PARSE_SUCCESS(Nam4, e<int>("abc???? abc"), (type{e<int>("abc"), {e<int>("??"), e<int>("??")}}), e<int>(" abc"));
        ASSERT_PARSE_FAILURE(Nam4, e<int>("ab???? abc"));
        ASSERT_PARSE_SUCCESS(Nam4, e<int>("abc?? ?? abc"), (type{e<int>("abc"), {e<int>("??")}}), e<int>(" ?? abc"));
    }
}

} // namespace
} // namespace k3::tok3n::tests
