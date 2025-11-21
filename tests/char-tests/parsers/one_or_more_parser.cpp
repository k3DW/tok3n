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
        EXPECT_THAT(the_parser<Oom1> | FAILS_PARSING("litera"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING("literal", vec_type({ "literal" }), ""));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING("literally", vec_type({ "literal" }), "ly"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING("literallitera", vec_type({ "literal" }), "litera"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING("literalliterallitera", vec_type({ "literal", "literal" }), "litera"));
        EXPECT_THAT(the_parser<Oom1> | FAILS_PARSING(" literalliterallitera"));
        EXPECT_THAT(the_parser<Oom1> | FAILS_PARSING(""));
    }

    {
        using vec_type = std::vector<output_span<wchar_t>>;
        EXPECT_THAT(the_parser<Oom1> | FAILS_PARSING(L"litera"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(L"literal", vec_type({ L"literal" }), L""));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(L"literally", vec_type({ L"literal" }), L"ly"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(L"literallitera", vec_type({ L"literal" }), L"litera"));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(L"literalliterallitera", vec_type({ L"literal", L"literal" }), L"litera"));
        EXPECT_THAT(the_parser<Oom1> | FAILS_PARSING(L" literalliterallitera"));
        EXPECT_THAT(the_parser<Oom1> | FAILS_PARSING(L""));
    }

    {
        using vec_type = std::vector<output_span<int>>;
        EXPECT_THAT(the_parser<Oom1> | FAILS_PARSING(e<int>("litera")));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(e<int>("literal"), vec_type({ arr_literal }), e<int>("")));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(e<int>("literally"), vec_type({ arr_literal }), e<int>("ly")));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(e<int>("literallitera"), vec_type({ arr_literal }), e<int>("litera")));
        EXPECT_THAT(the_parser<Oom1> | SUCCEEDS_PARSING(e<int>("literalliterallitera"), vec_type({ arr_literal, arr_literal }), e<int>("litera")));
        EXPECT_THAT(the_parser<Oom1> | FAILS_PARSING(e<int>(" literalliterallitera")));
        EXPECT_THAT(the_parser<Oom1> | FAILS_PARSING(e<int>("")));
    }
}
TEST("one_or_more_parser", "Parse one_or_more_parser<any_of_parser>")
{
    {
        using vec_type = std::vector<output_span<char>>;
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING("abcdef", vec_type({ "a", "b", "c" }), "def"));
        EXPECT_THAT(the_parser<Oom2> | FAILS_PARSING("fedcba"));
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING("cbabcccbjklmnop", vec_type({ "c", "b", "a", "b", "c", "c", "c", "b" }), "jklmnop"));
        EXPECT_THAT(the_parser<Oom2> | FAILS_PARSING(""));
    }

    {
        using vec_type = std::vector<output_span<wchar_t>>;
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING(L"abcdef", vec_type({ L"a", L"b", L"c" }), L"def"));
        EXPECT_THAT(the_parser<Oom2> | FAILS_PARSING(L"fedcba"));
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING(L"cbabcccbjklmnop", vec_type({ L"c", L"b", L"a", L"b", L"c", L"c", L"c", L"b" }), L"jklmnop"));
        EXPECT_THAT(the_parser<Oom2> | FAILS_PARSING(L""));
    }

    {
        using vec_type = std::vector<output_span<int>>;
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING(e<int>("abcdef"), vec_type({ arr_a, arr_b, arr_c }), e<int>("def")));
        EXPECT_THAT(the_parser<Oom2> | FAILS_PARSING(e<int>("fedcba")));
        EXPECT_THAT(the_parser<Oom2> | SUCCEEDS_PARSING(e<int>("cbabcccbjklmnop"), vec_type({ arr_c, arr_b, arr_a, arr_b, arr_c, arr_c, arr_c, arr_b }), e<int>("jklmnop")));
        EXPECT_THAT(the_parser<Oom2> | FAILS_PARSING(e<int>("")));
    }
}
TEST("one_or_more_parser", "Parse one_or_more_parser<choice_parser>")
{
    {
        using vec_type = std::vector<output_span<char>>;
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING("abliteralcbliteralcf", vec_type({ "a", "b", "literal", "c", "b", "literal", "c" }), "f"));
        EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING("abliteralcblitralcf", vec_type({ "a", "b", "literal", "c", "b" }), "litralcf"));
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING("literalabacliteral", vec_type({ "literal", "a", "b", "a", "c", "literal" }), ""));
        EXPECT_THAT(the_parser<Oom3> | FAILS_PARSING(""));
    }

    {
        using vec_type = std::vector<output_span<wchar_t>>;
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(L"abliteralcbliteralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b", L"literal", L"c" }), L"f"));
        EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(L"abliteralcblitralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b" }), L"litralcf"));
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(L"literalabacliteral", vec_type({ L"literal", L"a", L"b", L"a", L"c", L"literal" }), L""));
        EXPECT_THAT(the_parser<Oom3> | FAILS_PARSING(L""));
    }

    {
        using vec_type = std::vector<output_span<int>>;
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(e<int>("abliteralcbliteralcf"), vec_type({ arr_a, arr_b, arr_literal, arr_c, arr_b, arr_literal, arr_c }), e<int>("f")));
        EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(e<int>("abliteralcblitralcf"), vec_type({ arr_a, arr_b, arr_literal, arr_c, arr_b }), e<int>("litralcf")));
        // ICE: EXPECT_THAT(the_parser<Oom3> | SUCCEEDS_PARSING(e<int>("literalabacliteral"), vec_type({ arr_literal, arr_a, arr_b, arr_a, arr_c, arr_literal }), e<int>("")));
        EXPECT_THAT(the_parser<Oom3> | FAILS_PARSING(e<int>("")));
    }
}
TEST("one_or_more_parser", "Parse one_or_more_parser<sequence_parser>")
{
    {
        using vec_type = std::vector<std::tuple<output_span<char>, output_span<char>>>;
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralb", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), ""));
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralbliteral", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "literal"));
        EXPECT_THAT(the_parser<Oom4> | FAILS_PARSING("aliteralaliteralcliteralbliteral"));
        EXPECT_THAT(the_parser<Oom4> | FAILS_PARSING(""));
    }

    {
        using vec_type = std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>;
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralb", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L""));
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralbliteral", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"literal"));
        EXPECT_THAT(the_parser<Oom4> | FAILS_PARSING(L"aliteralaliteralcliteralbliteral"));
        EXPECT_THAT(the_parser<Oom4> | FAILS_PARSING(L""));
    }

    {
        using vec_type = std::vector<std::tuple<output_span<int>, output_span<int>>>;
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralb"), vec_type({ {arr_literal, arr_a}, {arr_literal, arr_c}, {arr_literal, arr_c}, {arr_literal, arr_b} }), e<int>("")));
        EXPECT_THAT(the_parser<Oom4> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralbliteral"), vec_type({ {arr_literal, arr_a}, {arr_literal, arr_c}, {arr_literal, arr_c}, {arr_literal, arr_b} }), e<int>("literal")));
        EXPECT_THAT(the_parser<Oom4> | FAILS_PARSING(e<int>("aliteralaliteralcliteralbliteral")));
        EXPECT_THAT(the_parser<Oom4> | FAILS_PARSING(e<int>("")));
    }
}

TEST("one_or_more_parser", "Parse one_or_more_parser<void-parser>")
{
    using P = one_or_more_parser<ignore_parser<ABC>>;

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abcabcabca", "a"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abcabca", "a"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abcabc", ""));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(" abcabc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abcab", "ab"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abc", ""));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abcabcabca", L"a"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abcabca", L"a"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abcabc", L""));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L" abcabc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abcab", L"ab"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abc", L""));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abcabcabca"), e<int>("a")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abcabca"), e<int>("a")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abcabc"), e<int>("")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>(" abcabc")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abcab"), e<int>("ab")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abc"), e<int>("")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>("")));
}

} // namespace
} // namespace k3::tok3n::tests
