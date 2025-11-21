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
    EXPECT_THAT(the_parser<Apf1> | has_family<filter_family>);

    EXPECT_THAT(the_parser<Apf1> | (is_parser_for<char>.with_result<std::tuple<output_span<char>, std::vector<output_span<char>>>>));

    EXPECT_THAT(the_parser<Apf1> | (is_parser_for<wchar_t>.with_result<std::tuple<output_span<wchar_t>, std::vector<output_span<wchar_t>>>>));

    EXPECT_THAT(the_parser<Apf1> | (is_parser_for<int>.with_result<std::tuple<output_span<int>, std::vector<output_span<int>>>>));
}

TEST("apply_filter_parser", "Parse all")
{
    {
        using vec_type = std::vector<output_span<char>>;
        using tuple_type = std::tuple<output_span<char>, vec_type>;
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING("abcabc", tuple_type("abc", {}), "abc"));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING("abc", tuple_type("abc", {}), ""));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING("abc?", tuple_type("abc", {}), "?"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, "abc??", "");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, "abc???", "?");
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING("abc????", tuple_type("abc", { "??", "??" }), ""));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING("abc?????", tuple_type("abc", { "??", "??" }), "?"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, "abc??????", "");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, "abc???????", "?");
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING("abc????????", tuple_type("abc", { "??", "??", "??", "??" }), ""));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING("abc?????????", tuple_type("abc", { "??", "??", "??", "??" }), "?"));
        ASSERT_PARSE_FAILURE(Apf1, "??abc???????");
        ASSERT_PARSE_FAILURE(Apf1, "");
    }

    {
        using vec_type = std::vector<output_span<wchar_t>>;
        using tuple_type = std::tuple<output_span<wchar_t>, vec_type>;
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(L"abcabc", tuple_type(L"abc", {}), L"abc"));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(L"abc", tuple_type(L"abc", {}), L""));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(L"abc?", tuple_type(L"abc", {}), L"?"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, L"abc??", L"");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, L"abc???", L"?");
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(L"abc????", tuple_type(L"abc", { L"??", L"??" }), L""));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(L"abc?????", tuple_type(L"abc", { L"??", L"??" }), L"?"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, L"abc??????", L"");
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, L"abc???????", L"?");
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(L"abc????????", tuple_type(L"abc", { L"??", L"??", L"??", L"??" }), L""));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(L"abc?????????", tuple_type(L"abc", { L"??", L"??", L"??", L"??" }), L"?"));
        ASSERT_PARSE_FAILURE(Apf1, L"??abc???????");
        ASSERT_PARSE_FAILURE(Apf1, L"");
    }

    {
        using vec_type = std::vector<output_span<int>>;
        using tuple_type = std::tuple<output_span<int>, vec_type>;
        static constexpr auto arr_abc = e<int>("abc");
        static constexpr auto arr_qq = e<int>("??");
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(e<int>("abcabc"), tuple_type(arr_abc, {}), e<int>("abc")));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(e<int>("abc"), tuple_type(arr_abc, {}), e<int>("")));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(e<int>("abc?"), tuple_type(arr_abc, {}), e<int>("?")));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, e<int>("abc??"), e<int>(""));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, e<int>("abc???"), e<int>("?"));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(e<int>("abc????"), tuple_type(arr_abc, { arr_qq, arr_qq }), e<int>("")));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(e<int>("abc?????"), tuple_type(arr_abc, { arr_qq, arr_qq }), e<int>("?")));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, e<int>("abc??????"), e<int>(""));
        ASSERT_PARSE_LOOKAHEAD_ONLY(Apf1, e<int>("abc???????"), e<int>("?"));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(e<int>("abc????????"), tuple_type(arr_abc, { arr_qq, arr_qq, arr_qq, arr_qq }), e<int>("")));
        EXPECT_THAT(the_parser<Apf1> | SUCCEEDS_PARSING(e<int>("abc?????????"), tuple_type(arr_abc, { arr_qq, arr_qq, arr_qq, arr_qq }), e<int>("?")));
        ASSERT_PARSE_FAILURE(Apf1, e<int>("??abc???????"));
        ASSERT_PARSE_FAILURE(Apf1, e<int>(""));
    }
}

} // namespace
} // namespace k3::tok3n::tests
