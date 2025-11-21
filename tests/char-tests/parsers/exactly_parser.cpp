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

FIXTURE("exactly_parser");

TEST("exactly_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Exa1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Exa2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Exa3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Exa4> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Exa1> | has_family<exactly_family>);
    EXPECT_THAT(the_parser<Exa2> | has_family<exactly_family>);
    EXPECT_THAT(the_parser<Exa3> | has_family<exactly_family>);
    EXPECT_THAT(the_parser<Exa4> | has_family<exactly_family>);

    EXPECT_THAT(the_parser<Exa1> | (is_parser_for<char>.with_result<std::array<output_span<char>, 3>>));
    EXPECT_THAT(the_parser<Exa2> | (is_parser_for<char>.with_result<std::array<output_span<char>, 5>>));
    EXPECT_THAT(the_parser<Exa3> | (is_parser_for<char>.with_result<std::array<output_span<char>, 4>>));
    EXPECT_THAT(the_parser<Exa4> | (is_parser_for<char>.with_result<std::array<std::tuple<output_span<char>, output_span<char>>, 2>>));

    EXPECT_THAT(the_parser<Exa1> | (is_parser_for<wchar_t>.with_result<std::array<output_span<wchar_t>, 3>>));
    EXPECT_THAT(the_parser<Exa2> | (is_parser_for<wchar_t>.with_result<std::array<output_span<wchar_t>, 5>>));
    EXPECT_THAT(the_parser<Exa3> | (is_parser_for<wchar_t>.with_result<std::array<output_span<wchar_t>, 4>>));
    EXPECT_THAT(the_parser<Exa4> | (is_parser_for<wchar_t>.with_result<std::array<std::tuple<output_span<wchar_t>, output_span<wchar_t>>, 2>>));

    EXPECT_THAT(the_parser<Exa1> | (is_parser_for<int>.with_result<std::array<output_span<int>, 3>>));
    EXPECT_THAT(the_parser<Exa2> | (is_parser_for<int>.with_result<std::array<output_span<int>, 5>>));
    EXPECT_THAT(the_parser<Exa3> | (is_parser_for<int>.with_result<std::array<output_span<int>, 4>>));
    EXPECT_THAT(the_parser<Exa4> | (is_parser_for<int>.with_result<std::array<std::tuple<output_span<int>, output_span<int>>, 2>>));
}

TEST("exactly_parser", "Constructibility")
{
    EXPECT_THAT((the_parser_family<exactly_parser>.is_not_valid_with<Any1, index_c<0>>));
    EXPECT_THAT((the_parser_family<exactly_parser>.is_valid_with<Any1, index_c<1>>));
    EXPECT_THAT((the_parser_family<exactly_parser>.is_valid_with<Any1, index_c<2>>));

    EXPECT_THAT((the_parser_family<exactly_parser>.is_not_valid_with<Any1, integral_constant<0>>));
    EXPECT_THAT((the_parser_family<exactly_parser>.is_not_valid_with<Any1, integral_constant<1>>));
    EXPECT_THAT((the_parser_family<exactly_parser>.is_not_valid_with<Any1, integral_constant<2>>));
}

TEST("exactly_parser", "Parse exactly_parser<all_of_parser>")
{
    {
        using array_type = std::array<output_span<char>, 3>;
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING("litera"));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING("literal"));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING("literalliteral"));
        EXPECT_THAT(the_parser<Exa1> | SUCCEEDS_PARSING("literalliteralliteral", array_type({ "literal", "literal", "literal" }), ""));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(" literalliteralliteral"));
        EXPECT_THAT(the_parser<Exa1> | SUCCEEDS_PARSING("literalliteralliteralliteral", array_type({ "literal", "literal", "literal" }), "literal"));
        EXPECT_THAT(the_parser<Exa1> | SUCCEEDS_PARSING("literalliteralliterallyliteral", array_type({ "literal", "literal", "literal" }), "lyliteral"));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(""));
    }

    {
        using array_type = std::array<output_span<wchar_t>, 3>;
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(L"litera"));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(L"literal"));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(L"literalliteral"));
        EXPECT_THAT(the_parser<Exa1> | SUCCEEDS_PARSING(L"literalliteralliteral", array_type({ L"literal", L"literal", L"literal" }), L""));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(L" literalliteralliteral"));
        EXPECT_THAT(the_parser<Exa1> | SUCCEEDS_PARSING(L"literalliteralliteralliteral", array_type({ L"literal", L"literal", L"literal" }), L"literal"));
        EXPECT_THAT(the_parser<Exa1> | SUCCEEDS_PARSING(L"literalliteralliterallyliteral", array_type({ L"literal", L"literal", L"literal" }), L"lyliteral"));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(L""));
    }

    {
        using array_type = std::array<output_span<int>, 3>;
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(e<int>("litera")));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(e<int>("literal")));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(e<int>("literalliteral")));
        EXPECT_THAT(the_parser<Exa1> | SUCCEEDS_PARSING(e<int>("literalliteralliteral"), array_type({ arr_literal, arr_literal, arr_literal }), e<int>()));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(e<int>(" literalliteralliteral")));
        EXPECT_THAT(the_parser<Exa1> | SUCCEEDS_PARSING(e<int>("literalliteralliteralliteral"), array_type({ arr_literal, arr_literal, arr_literal }), e<int>("literal")));
        EXPECT_THAT(the_parser<Exa1> | SUCCEEDS_PARSING(e<int>("literalliteralliterallyliteral"), array_type({ arr_literal, arr_literal, arr_literal }), e<int>("lyliteral")));
        EXPECT_THAT(the_parser<Exa1> | FAILS_PARSING(e<int>()));
    }
}
TEST("exactly_parser", "Parse exactly_parser<any_of_parser>")
{
    {
        using array_type = std::array<output_span<char>, 5>;
        EXPECT_THAT(the_parser<Exa2> | SUCCEEDS_PARSING("abcbaa", array_type({ "a", "b", "c", "b", "a" }), "a"));
        EXPECT_THAT(the_parser<Exa2> | FAILS_PARSING("fedcba"));
        EXPECT_THAT(the_parser<Exa2> | SUCCEEDS_PARSING("cbabcccbjklmnop", array_type({ "c", "b", "a", "b", "c" }), "ccbjklmnop"));
        EXPECT_THAT(the_parser<Exa2> | FAILS_PARSING(""));
    }

    {
        using array_type = std::array<output_span<wchar_t>, 5>;
        EXPECT_THAT(the_parser<Exa2> | SUCCEEDS_PARSING(L"abcbaa", array_type({ L"a", L"b", L"c", L"b", L"a" }), L"a"));
        EXPECT_THAT(the_parser<Exa2> | FAILS_PARSING(L"fedcba"));
        EXPECT_THAT(the_parser<Exa2> | SUCCEEDS_PARSING(L"cbabcccbjklmnop", array_type({ L"c", L"b", L"a", L"b", L"c" }), L"ccbjklmnop"));
        EXPECT_THAT(the_parser<Exa2> | FAILS_PARSING(L""));
    }

    {
        using array_type = std::array<output_span<int>, 5>;
        EXPECT_THAT(the_parser<Exa2> | SUCCEEDS_PARSING(e<int>("abcbaa"), array_type({ arr_a, arr_b, arr_c, arr_b, arr_a }), e<int>("a")));
        EXPECT_THAT(the_parser<Exa2> | FAILS_PARSING(e<int>("fedcba")));
        EXPECT_THAT(the_parser<Exa2> | SUCCEEDS_PARSING(e<int>("cbabcccbjklmnop"), array_type({ arr_c, arr_b, arr_a, arr_b, arr_c }), e<int>("ccbjklmnop")));
        EXPECT_THAT(the_parser<Exa2> | FAILS_PARSING(e<int>()));
    }
}
TEST("exactly_parser", "Parse exactly_parser<choice_parser>")
{
    {
        using array_type = std::array<output_span<char>, 4>;
        EXPECT_THAT(the_parser<Exa3> | SUCCEEDS_PARSING("abliteralcbliteralcf", array_type({ "a", "b", "literal", "c" }), "bliteralcf"));
        EXPECT_THAT(the_parser<Exa3> | SUCCEEDS_PARSING("abliteralcblitralcf", array_type({ "a", "b", "literal", "c" }), "blitralcf"));
        EXPECT_THAT(the_parser<Exa3> | SUCCEEDS_PARSING("literalabacliteral", array_type({ "literal", "a", "b", "a" }), "cliteral"));
        EXPECT_THAT(the_parser<Exa3> | FAILS_PARSING(""));
    }

    {
        using array_type = std::array<output_span<wchar_t>, 4>;
        EXPECT_THAT(the_parser<Exa3> | SUCCEEDS_PARSING(L"abliteralcbliteralcf", array_type({ L"a", L"b", L"literal", L"c" }), L"bliteralcf"));
        EXPECT_THAT(the_parser<Exa3> | SUCCEEDS_PARSING(L"abliteralcblitralcf", array_type({ L"a", L"b", L"literal", L"c" }), L"blitralcf"));
        EXPECT_THAT(the_parser<Exa3> | SUCCEEDS_PARSING(L"literalabacliteral", array_type({ L"literal", L"a", L"b", L"a" }), L"cliteral"));
        EXPECT_THAT(the_parser<Exa3> | FAILS_PARSING(L""));
    }

    {
        using array_type = std::array<output_span<int>, 4>;
        EXPECT_THAT(the_parser<Exa3> | SUCCEEDS_PARSING(e<int>("abliteralcbliteralcf"), array_type({ arr_a, arr_b, arr_literal, arr_c }), e<int>("bliteralcf")));
        EXPECT_THAT(the_parser<Exa3> | SUCCEEDS_PARSING(e<int>("abliteralcblitralcf"), array_type({ arr_a, arr_b, arr_literal, arr_c }), e<int>("blitralcf")));
        EXPECT_THAT(the_parser<Exa3> | SUCCEEDS_PARSING(e<int>("literalabacliteral"), array_type({ arr_literal, arr_a, arr_b, arr_a }), e<int>("cliteral")));
        EXPECT_THAT(the_parser<Exa3> | FAILS_PARSING(e<int>()));
    }
}
TEST("exactly_parser", "Parse exactly_parser<sequence_parser>")
{
    {
        using array_type = std::array<std::tuple<output_span<char>, output_span<char>>, 2>;
        EXPECT_THAT(the_parser<Exa4> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralb", array_type({ {"literal", "a"}, {"literal", "c"} }), "literalcliteralb"));
        EXPECT_THAT(the_parser<Exa4> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralbliteral", array_type({ {"literal", "a"}, {"literal", "c"} }), "literalcliteralbliteral"));
        EXPECT_THAT(the_parser<Exa4> | FAILS_PARSING("aliteralaliteralcliteralbliteral"));
        EXPECT_THAT(the_parser<Exa4> | FAILS_PARSING(""));
    }

    {
        using array_type = std::array<std::tuple<output_span<wchar_t>, output_span<wchar_t>>, 2>;
        EXPECT_THAT(the_parser<Exa4> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralb", array_type({ {L"literal", L"a"}, {L"literal", L"c"} }), L"literalcliteralb"));
        EXPECT_THAT(the_parser<Exa4> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralbliteral", array_type({ {L"literal", L"a"}, {L"literal", L"c"} }), L"literalcliteralbliteral"));
        EXPECT_THAT(the_parser<Exa4> | FAILS_PARSING(L"aliteralaliteralcliteralbliteral"));
        EXPECT_THAT(the_parser<Exa4> | FAILS_PARSING(L""));
    }

    {
        using array_type = std::array<std::tuple<output_span<int>, output_span<int>>, 2>;
        EXPECT_THAT(the_parser<Exa4> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralb"), array_type({ {arr_literal, arr_a}, {arr_literal, arr_c} }), e<int>("literalcliteralb")));
        EXPECT_THAT(the_parser<Exa4> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralbliteral"), array_type({ {arr_literal, arr_a}, {arr_literal, arr_c} }), e<int>("literalcliteralbliteral")));
        EXPECT_THAT(the_parser<Exa4> | FAILS_PARSING(e<int>("aliteralaliteralcliteralbliteral")));
        EXPECT_THAT(the_parser<Exa4> | FAILS_PARSING(e<int>()));
    }
}

TEST("exactly_parser", "Parse exactly_parser<void-parser>")
{
    using P = exactly_parser<ignore_parser<ABC>, index_c<2>>;

    ASSERT_PARSE_SUCCESS_VOID(P, "abcabcabca", "abca");
    ASSERT_PARSE_SUCCESS_VOID(P, "abcabca", "a");
    ASSERT_PARSE_SUCCESS_VOID(P, "abcabc", "");
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(" abcabc"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING("abcab"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING("abc"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(""));

    ASSERT_PARSE_SUCCESS_VOID(P, L"abcabcabca", L"abca");
    ASSERT_PARSE_SUCCESS_VOID(P, L"abcabca", L"a");
    ASSERT_PARSE_SUCCESS_VOID(P, L"abcabc", L"");
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L" abcabc"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L"abcab"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L"abc"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L""));

    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabcabca"), e<int>("abca"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabca"), e<int>("a"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabc"), e<int>(""));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>(" abcabc")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>("abcab")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>("abc")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>("")));
}

} // namespace
} // namespace k3::tok3n::tests
