// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("maybe_parser");

TEST("maybe_parser", "Requirements")
{
    EXPECT_THAT(the_parser<May1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<May2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<May3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<May4> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<May1> | has_family<maybe_family>);
    EXPECT_THAT(the_parser<May2> | has_family<maybe_family>);
    EXPECT_THAT(the_parser<May3> | has_family<maybe_family>);
    EXPECT_THAT(the_parser<May4> | has_family<maybe_family>);

    EXPECT_THAT(the_parser<May1> | is_parser_for<char>.with_result<std::optional<output_span<char>>>);
    EXPECT_THAT(the_parser<May2> | is_parser_for<char>.with_result<std::optional<output_span<char>>>);
    EXPECT_THAT(the_parser<May3> | is_parser_for<char>.with_result<std::optional<output_span<char>>>);
    EXPECT_THAT(the_parser<May4> | (is_parser_for<char>.with_result<std::optional<std::tuple<output_span<char>, output_span<char>>>>));

    EXPECT_THAT(the_parser<May1> | is_parser_for<wchar_t>.with_result<std::optional<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<May2> | is_parser_for<wchar_t>.with_result<std::optional<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<May3> | is_parser_for<wchar_t>.with_result<std::optional<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<May4> | (is_parser_for<wchar_t>.with_result<std::optional<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>>));

    EXPECT_THAT(the_parser<May1> | is_parser_for<int>.with_result<std::optional<output_span<int>>>);
    EXPECT_THAT(the_parser<May2> | is_parser_for<int>.with_result<std::optional<output_span<int>>>);
    EXPECT_THAT(the_parser<May3> | is_parser_for<int>.with_result<std::optional<output_span<int>>>);
    EXPECT_THAT(the_parser<May4> | (is_parser_for<int>.with_result<std::optional<std::tuple<output_span<int>, output_span<int>>>>));
}

TEST("maybe_parser", "Parse maybe_parser<all_of_parser>")
{
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING("litera", std::nullopt, "litera"));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING("literal", std::optional("literal"), ""));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING("literally", std::optional("literal"), "ly"));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING("literallitera", std::optional("literal"), "litera"));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING("literalliterallitera", std::optional("literal"), "literallitera"));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(" literalliterallitera", std::nullopt, " literalliterallitera"));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING("", std::nullopt, ""));

    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(L"litera", std::nullopt, L"litera"));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(L"literal", std::optional(L"literal"), L""));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(L"literally", std::optional(L"literal"), L"ly"));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(L"literallitera", std::optional(L"literal"), L"litera"));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(L"literalliterallitera", std::optional(L"literal"), L"literallitera"));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(L" literalliterallitera", std::nullopt, L" literalliterallitera"));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(L"", std::nullopt, L""));

    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(e<int>("litera"), std::nullopt, e<int>("litera")));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(e<int>("literal"), std::optional(e<int>("literal")), e<int>("")));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(e<int>("literally"), std::optional(e<int>("literal")), e<int>("ly")));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(e<int>("literallitera"), std::optional(e<int>("literal")), e<int>("litera")));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(e<int>("literalliterallitera"), std::optional(e<int>("literal")), e<int>("literallitera")));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(e<int>(" literalliterallitera"), std::nullopt, e<int>(" literalliterallitera")));
    EXPECT_THAT(the_parser<May1> | SUCCEEDS_PARSING(e<int>(""), std::nullopt, e<int>("")));
}
TEST("maybe_parser", "Parse maybe_parser<any_of_parser>")
{
    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING("abcdef", std::optional("a"), "bcdef"));
    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING("fedcba", std::nullopt, "fedcba"));
    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING("cbabcccbjklmnop", std::optional("c"), "babcccbjklmnop"));
    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING("", std::nullopt, ""));

    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING(L"abcdef", std::optional(L"a"), L"bcdef"));
    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING(L"fedcba", std::nullopt, L"fedcba"));
    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING(L"cbabcccbjklmnop", std::optional(L"c"), L"babcccbjklmnop"));
    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING(L"", std::nullopt, L""));

    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING(e<int>("abcdef"), std::optional(e<int>("a")), e<int>("bcdef")));
    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING(e<int>("fedcba"), std::nullopt, e<int>("fedcba")));
    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING(e<int>("cbabcccbjklmnop"), std::optional(e<int>("c")), e<int>("babcccbjklmnop")));
    EXPECT_THAT(the_parser<May2> | SUCCEEDS_PARSING(e<int>(""), std::nullopt, e<int>("")));
}
TEST("maybe_parser", "Parse maybe_parser<choice_parser>")
{
    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING("abliteralcbliteralcf", std::optional("a"), "bliteralcbliteralcf"));
    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING("abliteralcblitralcf", std::optional("a"), "bliteralcblitralcf"));
    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING("literalabacliteral", std::optional("literal"), "abacliteral"));
    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING("", std::nullopt, ""));

    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING(L"abliteralcbliteralcf", std::optional(L"a"), L"bliteralcbliteralcf"));
    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING(L"abliteralcblitralcf", std::optional(L"a"), L"bliteralcblitralcf"));
    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING(L"literalabacliteral", std::optional(L"literal"), L"abacliteral"));
    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING(L"", std::nullopt, L""));

    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING(e<int>("abliteralcbliteralcf"), std::optional(e<int>("a")), e<int>("bliteralcbliteralcf")));
    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING(e<int>("abliteralcblitralcf"), std::optional(e<int>("a")), e<int>("bliteralcblitralcf")));
    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING(e<int>("literalabacliteral"), std::optional(e<int>("literal")), e<int>("abacliteral")));
    EXPECT_THAT(the_parser<May3> | SUCCEEDS_PARSING(e<int>(""), std::nullopt, e<int>("")));
}
TEST("maybe_parser", "Parse maybe_parser<sequence_parser>")
{
    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralb", std::optional(std::tuple("literal", "a")), "literalcliteralcliteralb"));
    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralbliteral", std::optional(std::tuple("literal", "a")), "literalcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING("aliteralaliteralcliteralbliteral", std::nullopt, "aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING("", std::nullopt, ""));

    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralb", std::optional(std::tuple(L"literal", L"a")), L"literalcliteralcliteralb"));
    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralbliteral", std::optional(std::tuple(L"literal", L"a")), L"literalcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING(L"aliteralaliteralcliteralbliteral", std::nullopt, L"aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING(L"", std::nullopt, L""));

    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralb"), std::optional(std::tuple(e<int>("literal"), e<int>("a"))), e<int>("literalcliteralcliteralb")));
    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralbliteral"), std::optional(std::tuple(e<int>("literal"), e<int>("a"))), e<int>("literalcliteralcliteralbliteral")));
    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING(e<int>("aliteralaliteralcliteralbliteral"), std::nullopt, e<int>("aliteralaliteralcliteralbliteral")));
    EXPECT_THAT(the_parser<May4> | SUCCEEDS_PARSING(e<int>(""), std::nullopt, e<int>("")));
}

TEST("maybe_parser", "Parse maybe_parser<void-parser>")
{
    using P = maybe_parser<ignore_parser<ABC>>;

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abcabcabca", "abcabca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abcabca", "abca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abcabc", "abc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(" abcabc", " abcabc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abcab", "ab"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abc", ""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("", ""));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abcabcabca", L"abcabca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abcabca", L"abca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abcabc", L"abc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L" abcabc", L" abcabc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abcab", L"ab"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abc", L""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"", L""));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abcabcabca"), e<int>("abcabca")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abcabca"), e<int>("abca")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abcabc"), e<int>("abc")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>(" abcabc"), e<int>(" abcabc")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abcab"), e<int>("ab")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abc"), e<int>("")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>(""), e<int>("")));
}

} // namespace
} // namespace k3::tok3n::tests
