// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

constexpr auto arr_literal = e<int>("literal");
constexpr auto arr_a = e<int>("a");
constexpr auto arr_b = e<int>("b");
constexpr auto arr_c = e<int>("c");

FIXTURE("one_or_more_parser");

TEST("one_or_more_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Oom1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Oom2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Oom3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Oom4> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Oom1> | has_family<one_or_more_family>);
    EXPECT_THAT(the_parser<Oom2> | has_family<one_or_more_family>);
    EXPECT_THAT(the_parser<Oom3> | has_family<one_or_more_family>);
    EXPECT_THAT(the_parser<Oom4> | has_family<one_or_more_family>);

    EXPECT_THAT(the_parser<Oom1> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Oom2> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Oom3> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Oom4> | (is_parser_for<char>.with_result<std::vector<std::tuple<output_span<char>, output_span<char>>>>));

    EXPECT_THAT(the_parser<Oom1> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Oom2> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Oom3> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Oom4> | (is_parser_for<wchar_t>.with_result<std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>>));

    EXPECT_THAT(the_parser<Oom1> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Oom2> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Oom3> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Oom4> | (is_parser_for<int>.with_result<std::vector<std::tuple<output_span<int>, output_span<int>>>>));
}

TEST("one_or_more_parser", "Parse one_or_more_parser<all_of_parser>")
{
    {
        using vec_type = std::vector<output_span<char>>;
        ASSERT_PARSE_FAILURE(Oom1, "litera");
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING("literal", vec_type({ "literal" }), ""));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING("literally", vec_type({ "literal" }), "ly"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING("literallitera", vec_type({ "literal" }), "litera"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING("literalliterallitera", vec_type({ "literal", "literal" }), "litera"));
        ASSERT_PARSE_FAILURE(Oom1, " literalliterallitera");
        ASSERT_PARSE_FAILURE(Oom1, "");
    }

    {
        using vec_type = std::vector<output_span<wchar_t>>;
        ASSERT_PARSE_FAILURE(Oom1, L"litera");
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(L"literal", vec_type({ L"literal" }), L""));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(L"literally", vec_type({ L"literal" }), L"ly"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(L"literallitera", vec_type({ L"literal" }), L"litera"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(L"literalliterallitera", vec_type({ L"literal", L"literal" }), L"litera"));
        ASSERT_PARSE_FAILURE(Oom1, L" literalliterallitera");
        ASSERT_PARSE_FAILURE(Oom1, L"");
    }

    {
        using vec_type = std::vector<output_span<int>>;
        ASSERT_PARSE_FAILURE(Oom1, e<int>("litera"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(e<int>("literal"), vec_type({ arr_literal }), e<int>("")));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(e<int>("literally"), vec_type({ arr_literal }), e<int>("ly")));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(e<int>("literallitera"), vec_type({ arr_literal }), e<int>("litera")));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(e<int>("literalliterallitera"), vec_type({ arr_literal, arr_literal }), e<int>("litera")));
        ASSERT_PARSE_FAILURE(Oom1, e<int>(" literalliterallitera"));
        ASSERT_PARSE_FAILURE(Oom1, e<int>(""));
    }
}
TEST("one_or_more_parser", "Parse one_or_more_parser<any_of_parser>")
{
    {
        using vec_type = std::vector<output_span<char>>;
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING("abcdef", vec_type({ "a", "b", "c" }), "def"));
        ASSERT_PARSE_FAILURE(Oom2, "fedcba");
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING("cbabcccbjklmnop", vec_type({ "c", "b", "a", "b", "c", "c", "c", "b" }), "jklmnop"));
        ASSERT_PARSE_FAILURE(Oom2, "");
    }

    {
        using vec_type = std::vector<output_span<wchar_t>>;
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING(L"abcdef", vec_type({ L"a", L"b", L"c" }), L"def"));
        ASSERT_PARSE_FAILURE(Oom2, L"fedcba");
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING(L"cbabcccbjklmnop", vec_type({ L"c", L"b", L"a", L"b", L"c", L"c", L"c", L"b" }), L"jklmnop"));
        ASSERT_PARSE_FAILURE(Oom2, L"");
    }

    {
        using vec_type = std::vector<output_span<int>>;
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING(e<int>("abcdef"), vec_type({ arr_a, arr_b, arr_c }), e<int>("def")));
        ASSERT_PARSE_FAILURE(Oom2, e<int>("fedcba"));
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING(e<int>("cbabcccbjklmnop"), vec_type({ arr_c, arr_b, arr_a, arr_b, arr_c, arr_c, arr_c, arr_b }), e<int>("jklmnop")));
        ASSERT_PARSE_FAILURE(Oom2, e<int>(""));
    }
}
TEST("one_or_more_parser", "Parse one_or_more_parser<choice_parser>")
{
    {
        using vec_type = std::vector<output_span<char>>;
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING("abliteralcbliteralcf", vec_type({ "a", "b", "literal", "c", "b", "literal", "c" }), "f"));
        EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING("abliteralcblitralcf", vec_type({ "a", "b", "literal", "c", "b" }), "litralcf"));
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING("literalabacliteral", vec_type({ "literal", "a", "b", "a", "c", "literal" }), ""));
        ASSERT_PARSE_FAILURE(Oom3, "");
    }

    {
        using vec_type = std::vector<output_span<wchar_t>>;
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(L"abliteralcbliteralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b", L"literal", L"c" }), L"f"));
        EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(L"abliteralcblitralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b" }), L"litralcf"));
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(L"literalabacliteral", vec_type({ L"literal", L"a", L"b", L"a", L"c", L"literal" }), L""));
        ASSERT_PARSE_FAILURE(Oom3, L"");
    }

    {
        using vec_type = std::vector<output_span<int>>;
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(e<int>("abliteralcbliteralcf"), vec_type({ arr_a, arr_b, arr_literal, arr_c, arr_b, arr_literal, arr_c }), e<int>("f")));
        EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(e<int>("abliteralcblitralcf"), vec_type({ arr_a, arr_b, arr_literal, arr_c, arr_b }), e<int>("litralcf")));
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(e<int>("literalabacliteral"), vec_type({ arr_literal, arr_a, arr_b, arr_a, arr_c, arr_literal }), e<int>("")));
        ASSERT_PARSE_FAILURE(Oom3, e<int>(""));
    }
}
TEST("one_or_more_parser", "Parse one_or_more_parser<sequence_parser>")
{
    {
        using vec_type = std::vector<std::tuple<output_span<char>, output_span<char>>>;
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralb", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), ""));
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralbliteral", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "literal"));
        ASSERT_PARSE_FAILURE(Oom4, "aliteralaliteralcliteralbliteral");
        ASSERT_PARSE_FAILURE(Oom4, "");
    }

    {
        using vec_type = std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>;
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralb", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L""));
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralbliteral", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"literal"));
        ASSERT_PARSE_FAILURE(Oom4, L"aliteralaliteralcliteralbliteral");
        ASSERT_PARSE_FAILURE(Oom4, L"");
    }

    {
        using vec_type = std::vector<std::tuple<output_span<int>, output_span<int>>>;
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralb"), vec_type({ {arr_literal, arr_a}, {arr_literal, arr_c}, {arr_literal, arr_c}, {arr_literal, arr_b} }), e<int>("")));
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralbliteral"), vec_type({ {arr_literal, arr_a}, {arr_literal, arr_c}, {arr_literal, arr_c}, {arr_literal, arr_b} }), e<int>("literal")));
        ASSERT_PARSE_FAILURE(Oom4, e<int>("aliteralaliteralcliteralbliteral"));
        ASSERT_PARSE_FAILURE(Oom4, e<int>(""));
    }
}

TEST("one_or_more_parser", "Parse one_or_more_parser<void-parser>")
{
    using P = one_or_more_parser<ignore_parser<ABC>>;

    ASSERT_PARSE_SUCCESS_VOID(P, "abcabcabca", "a");
    ASSERT_PARSE_SUCCESS_VOID(P, "abcabca", "a");
    ASSERT_PARSE_SUCCESS_VOID(P, "abcabc", "");
    ASSERT_PARSE_FAILURE(P, " abcabc");
    ASSERT_PARSE_SUCCESS_VOID(P, "abcab", "ab");
    ASSERT_PARSE_SUCCESS_VOID(P, "abc", "");
    ASSERT_PARSE_FAILURE(P, "");

    ASSERT_PARSE_SUCCESS_VOID(P, L"abcabcabca", L"a");
    ASSERT_PARSE_SUCCESS_VOID(P, L"abcabca", L"a");
    ASSERT_PARSE_SUCCESS_VOID(P, L"abcabc", L"");
    ASSERT_PARSE_FAILURE(P, L" abcabc");
    ASSERT_PARSE_SUCCESS_VOID(P, L"abcab", L"ab");
    ASSERT_PARSE_SUCCESS_VOID(P, L"abc", L"");
    ASSERT_PARSE_FAILURE(P, L"");

    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabcabca"), e<int>("a"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabca"), e<int>("a"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabc"), e<int>(""));
    ASSERT_PARSE_FAILURE(P, e<int>(" abcabc"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcab"), e<int>("ab"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abc"), e<int>(""));
    ASSERT_PARSE_FAILURE(P, e<int>(""));
}

} // namespace
} // namespace k3::tok3n::tests
