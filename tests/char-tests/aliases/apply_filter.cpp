// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("apply_filter_parser");

TEST("apply_filter_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Apf1> | has_value_type<value_type>);

    ASSERT_IS_PARSER(Apf1, char, filter_family, std::tuple<output_span<char>, std::vector<output_span<char>>>);

    ASSERT_IS_PARSER(Apf1, wchar_t, filter_family, std::tuple<output_span<wchar_t>, std::vector<output_span<wchar_t>>>);

    ASSERT_IS_PARSER(Apf1, int, filter_family, std::tuple<output_span<int>, std::vector<output_span<int>>>);
}

TEST("apply_filter_parser", "Parse all")
{
    {
        using vec_type = std::vector<output_span<char>>;
        using tuple_type = std::tuple<output_span<char>, vec_type>;
        ASSERT_PARSE_SUCCESS(Apf1, "abcabc", tuple_type("abc", {}), "abc");
        ASSERT_PARSE_SUCCESS(Apf1, "abc", tuple_type("abc", {}), "");
        ASSERT_PARSE_SUCCESS(Apf1, "abc?", tuple_type("abc", {}), "?");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, "abc??", "");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, "abc???", "?");
        ASSERT_PARSE_SUCCESS(Apf1, "abc????", tuple_type("abc", { "??", "??" }), "");
        ASSERT_PARSE_SUCCESS(Apf1, "abc?????", tuple_type("abc", { "??", "??" }), "?");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, "abc??????", "");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, "abc???????", "?");
        ASSERT_PARSE_SUCCESS(Apf1, "abc????????", tuple_type("abc", { "??", "??", "??", "??" }), "");
        ASSERT_PARSE_SUCCESS(Apf1, "abc?????????", tuple_type("abc", { "??", "??", "??", "??" }), "?");
        ASSERT_PARSE_FAILURE(Apf1, "??abc???????");
        ASSERT_PARSE_FAILURE(Apf1, "");
    }

    {
        using vec_type = std::vector<output_span<wchar_t>>;
        using tuple_type = std::tuple<output_span<wchar_t>, vec_type>;
        ASSERT_PARSE_SUCCESS(Apf1, L"abcabc", tuple_type(L"abc", {}), L"abc");
        ASSERT_PARSE_SUCCESS(Apf1, L"abc", tuple_type(L"abc", {}), L"");
        ASSERT_PARSE_SUCCESS(Apf1, L"abc?", tuple_type(L"abc", {}), L"?");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, L"abc??", L"");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, L"abc???", L"?");
        ASSERT_PARSE_SUCCESS(Apf1, L"abc????", tuple_type(L"abc", { L"??", L"??" }), L"");
        ASSERT_PARSE_SUCCESS(Apf1, L"abc?????", tuple_type(L"abc", { L"??", L"??" }), L"?");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, L"abc??????", L"");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, L"abc???????", L"?");
        ASSERT_PARSE_SUCCESS(Apf1, L"abc????????", tuple_type(L"abc", { L"??", L"??", L"??", L"??" }), L"");
        ASSERT_PARSE_SUCCESS(Apf1, L"abc?????????", tuple_type(L"abc", { L"??", L"??", L"??", L"??" }), L"?");
        ASSERT_PARSE_FAILURE(Apf1, L"??abc???????");
        ASSERT_PARSE_FAILURE(Apf1, L"");
    }

    {
        using vec_type = std::vector<output_span<int>>;
        using tuple_type = std::tuple<output_span<int>, vec_type>;
        ASSERT_PARSE_SUCCESS(Apf1, e<int>("abcabc"), tuple_type(e<int>("abc"), {}), e<int>("abc"));
        ASSERT_PARSE_SUCCESS(Apf1, e<int>("abc"), tuple_type(e<int>("abc"), {}), e<int>(""));
        ASSERT_PARSE_SUCCESS(Apf1, e<int>("abc?"), tuple_type(e<int>("abc"), {}), e<int>("?"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, e<int>("abc??"), e<int>(""));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, e<int>("abc???"), e<int>("?"));
        ASSERT_PARSE_SUCCESS(Apf1, e<int>("abc????"), tuple_type(e<int>("abc"), { e<int>("??"), e<int>("??") }), e<int>(""));
        ASSERT_PARSE_SUCCESS(Apf1, e<int>("abc?????"), tuple_type(e<int>("abc"), { e<int>("??"), e<int>("??") }), e<int>("?"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, e<int>("abc??????"), e<int>(""));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, e<int>("abc???????"), e<int>("?"));
        ASSERT_PARSE_SUCCESS(Apf1, e<int>("abc????????"), tuple_type(e<int>("abc"), { e<int>("??"), e<int>("??"), e<int>("??"), e<int>("??") }), e<int>(""));
        ASSERT_PARSE_SUCCESS(Apf1, e<int>("abc?????????"), tuple_type(e<int>("abc"), { e<int>("??"), e<int>("??"), e<int>("??"), e<int>("??") }), e<int>("?"));
        ASSERT_PARSE_FAILURE(Apf1, e<int>("??abc???????"));
        ASSERT_PARSE_FAILURE(Apf1, e<int>(""));
    }
}

} // namespace
} // namespace k3::tok3n::tests
