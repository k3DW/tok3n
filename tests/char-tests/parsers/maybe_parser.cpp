// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("maybe_parser");

TEST("maybe_parser", "Requirements")
{
    ASSERT_PARSER_VALUE_TYPE(May1, value_type);
    ASSERT_PARSER_VALUE_TYPE(May2, value_type);
    ASSERT_PARSER_VALUE_TYPE(May3, value_type);
    ASSERT_PARSER_VALUE_TYPE(May4, value_type);

    ASSERT_IS_PARSER(May1, char, maybe_family, std::optional<output_span<char>>);
    ASSERT_IS_PARSER(May2, char, maybe_family, std::optional<output_span<char>>);
    ASSERT_IS_PARSER(May3, char, maybe_family, std::optional<output_span<char>>);
    ASSERT_IS_PARSER(May4, char, maybe_family, std::optional<std::tuple<output_span<char>, output_span<char>>>);

    ASSERT_IS_PARSER(May1, wchar_t, maybe_family, std::optional<output_span<wchar_t>>);
    ASSERT_IS_PARSER(May2, wchar_t, maybe_family, std::optional<output_span<wchar_t>>);
    ASSERT_IS_PARSER(May3, wchar_t, maybe_family, std::optional<output_span<wchar_t>>);
    ASSERT_IS_PARSER(May4, wchar_t, maybe_family, std::optional<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>);

    ASSERT_IS_PARSER(May1, int, maybe_family, std::optional<output_span<int>>);
    ASSERT_IS_PARSER(May2, int, maybe_family, std::optional<output_span<int>>);
    ASSERT_IS_PARSER(May3, int, maybe_family, std::optional<output_span<int>>);
    ASSERT_IS_PARSER(May4, int, maybe_family, std::optional<std::tuple<output_span<int>, output_span<int>>>);
}

TEST("maybe_parser", "Parse maybe_parser<all_of_parser>")
{
    ASSERT_PARSE_SUCCESS(May1, "litera", std::nullopt, "litera");
    ASSERT_PARSE_SUCCESS(May1, "literal", std::optional("literal"), "");
    ASSERT_PARSE_SUCCESS(May1, "literally", std::optional("literal"), "ly");
    ASSERT_PARSE_SUCCESS(May1, "literallitera", std::optional("literal"), "litera");
    ASSERT_PARSE_SUCCESS(May1, "literalliterallitera", std::optional("literal"), "literallitera");
    ASSERT_PARSE_SUCCESS(May1, " literalliterallitera", std::nullopt, " literalliterallitera");
    ASSERT_PARSE_SUCCESS(May1, "", std::nullopt, "");

    ASSERT_PARSE_SUCCESS(May1, L"litera", std::nullopt, L"litera");
    ASSERT_PARSE_SUCCESS(May1, L"literal", std::optional(L"literal"), L"");
    ASSERT_PARSE_SUCCESS(May1, L"literally", std::optional(L"literal"), L"ly");
    ASSERT_PARSE_SUCCESS(May1, L"literallitera", std::optional(L"literal"), L"litera");
    ASSERT_PARSE_SUCCESS(May1, L"literalliterallitera", std::optional(L"literal"), L"literallitera");
    ASSERT_PARSE_SUCCESS(May1, L" literalliterallitera", std::nullopt, L" literalliterallitera");
    ASSERT_PARSE_SUCCESS(May1, L"", std::nullopt, L"");

    ASSERT_PARSE_SUCCESS(May1, e<int>("litera"), std::nullopt, e<int>("litera"));
    ASSERT_PARSE_SUCCESS(May1, e<int>("literal"), std::optional(e<int>("literal")), e<int>(""));
    ASSERT_PARSE_SUCCESS(May1, e<int>("literally"), std::optional(e<int>("literal")), e<int>("ly"));
    ASSERT_PARSE_SUCCESS(May1, e<int>("literallitera"), std::optional(e<int>("literal")), e<int>("litera"));
    ASSERT_PARSE_SUCCESS(May1, e<int>("literalliterallitera"), std::optional(e<int>("literal")), e<int>("literallitera"));
    ASSERT_PARSE_SUCCESS(May1, e<int>(" literalliterallitera"), std::nullopt, e<int>(" literalliterallitera"));
    ASSERT_PARSE_SUCCESS(May1, e<int>(""), std::nullopt, e<int>(""));
}
TEST("maybe_parser", "Parse maybe_parser<any_of_parser>")
{
    ASSERT_PARSE_SUCCESS(May2, "abcdef", std::optional("a"), "bcdef");
    ASSERT_PARSE_SUCCESS(May2, "fedcba", std::nullopt, "fedcba");
    ASSERT_PARSE_SUCCESS(May2, "cbabcccbjklmnop", std::optional("c"), "babcccbjklmnop");
    ASSERT_PARSE_SUCCESS(May2, "", std::nullopt, "");

    ASSERT_PARSE_SUCCESS(May2, L"abcdef", std::optional(L"a"), L"bcdef");
    ASSERT_PARSE_SUCCESS(May2, L"fedcba", std::nullopt, L"fedcba");
    ASSERT_PARSE_SUCCESS(May2, L"cbabcccbjklmnop", std::optional(L"c"), L"babcccbjklmnop");
    ASSERT_PARSE_SUCCESS(May2, L"", std::nullopt, L"");

    ASSERT_PARSE_SUCCESS(May2, e<int>("abcdef"), std::optional(e<int>("a")), e<int>("bcdef"));
    ASSERT_PARSE_SUCCESS(May2, e<int>("fedcba"), std::nullopt, e<int>("fedcba"));
    ASSERT_PARSE_SUCCESS(May2, e<int>("cbabcccbjklmnop"), std::optional(e<int>("c")), e<int>("babcccbjklmnop"));
    ASSERT_PARSE_SUCCESS(May2, e<int>(""), std::nullopt, e<int>(""));
}
TEST("maybe_parser", "Parse maybe_parser<choice_parser>")
{
    ASSERT_PARSE_SUCCESS(May3, "abliteralcbliteralcf", std::optional("a"), "bliteralcbliteralcf");
    ASSERT_PARSE_SUCCESS(May3, "abliteralcblitralcf", std::optional("a"), "bliteralcblitralcf");
    ASSERT_PARSE_SUCCESS(May3, "literalabacliteral", std::optional("literal"), "abacliteral");
    ASSERT_PARSE_SUCCESS(May3, "", std::nullopt, "");

    ASSERT_PARSE_SUCCESS(May3, L"abliteralcbliteralcf", std::optional(L"a"), L"bliteralcbliteralcf");
    ASSERT_PARSE_SUCCESS(May3, L"abliteralcblitralcf", std::optional(L"a"), L"bliteralcblitralcf");
    ASSERT_PARSE_SUCCESS(May3, L"literalabacliteral", std::optional(L"literal"), L"abacliteral");
    ASSERT_PARSE_SUCCESS(May3, L"", std::nullopt, L"");

    ASSERT_PARSE_SUCCESS(May3, e<int>("abliteralcbliteralcf"), std::optional(e<int>("a")), e<int>("bliteralcbliteralcf"));
    ASSERT_PARSE_SUCCESS(May3, e<int>("abliteralcblitralcf"), std::optional(e<int>("a")), e<int>("bliteralcblitralcf"));
    ASSERT_PARSE_SUCCESS(May3, e<int>("literalabacliteral"), std::optional(e<int>("literal")), e<int>("abacliteral"));
    ASSERT_PARSE_SUCCESS(May3, e<int>(""), std::nullopt, e<int>(""));
}
TEST("maybe_parser", "Parse maybe_parser<sequence_parser>")
{
    ASSERT_PARSE_SUCCESS(May4, "literalaliteralcliteralcliteralb", std::optional(std::tuple("literal", "a")), "literalcliteralcliteralb");
    ASSERT_PARSE_SUCCESS(May4, "literalaliteralcliteralcliteralbliteral", std::optional(std::tuple("literal", "a")), "literalcliteralcliteralbliteral");
    ASSERT_PARSE_SUCCESS(May4, "aliteralaliteralcliteralbliteral", std::nullopt, "aliteralaliteralcliteralbliteral");
    ASSERT_PARSE_SUCCESS(May4, "", std::nullopt, "");

    ASSERT_PARSE_SUCCESS(May4, L"literalaliteralcliteralcliteralb", std::optional(std::tuple(L"literal", L"a")), L"literalcliteralcliteralb");
    ASSERT_PARSE_SUCCESS(May4, L"literalaliteralcliteralcliteralbliteral", std::optional(std::tuple(L"literal", L"a")), L"literalcliteralcliteralbliteral");
    ASSERT_PARSE_SUCCESS(May4, L"aliteralaliteralcliteralbliteral", std::nullopt, L"aliteralaliteralcliteralbliteral");
    ASSERT_PARSE_SUCCESS(May4, L"", std::nullopt, L"");

    ASSERT_PARSE_SUCCESS(May4, e<int>("literalaliteralcliteralcliteralb"), std::optional(std::tuple(e<int>("literal"), e<int>("a"))), e<int>("literalcliteralcliteralb"));
    ASSERT_PARSE_SUCCESS(May4, e<int>("literalaliteralcliteralcliteralbliteral"), std::optional(std::tuple(e<int>("literal"), e<int>("a"))), e<int>("literalcliteralcliteralbliteral"));
    ASSERT_PARSE_SUCCESS(May4, e<int>("aliteralaliteralcliteralbliteral"), std::nullopt, e<int>("aliteralaliteralcliteralbliteral"));
    ASSERT_PARSE_SUCCESS(May4, e<int>(""), std::nullopt, e<int>(""));
}

TEST("maybe_parser", "Parse maybe_parser<void-parser>")
{
    using P = maybe_parser<ignore_parser<ABC>>;

    ASSERT_PARSE_SUCCESS_VOID(P, "abcabcabca", "abcabca");
    ASSERT_PARSE_SUCCESS_VOID(P, "abcabca", "abca");
    ASSERT_PARSE_SUCCESS_VOID(P, "abcabc", "abc");
    ASSERT_PARSE_SUCCESS_VOID(P, " abcabc", " abcabc");
    ASSERT_PARSE_SUCCESS_VOID(P, "abcab", "ab");
    ASSERT_PARSE_SUCCESS_VOID(P, "abc", "");
    ASSERT_PARSE_SUCCESS_VOID(P, "", "");

    ASSERT_PARSE_SUCCESS_VOID(P, L"abcabcabca", L"abcabca");
    ASSERT_PARSE_SUCCESS_VOID(P, L"abcabca", L"abca");
    ASSERT_PARSE_SUCCESS_VOID(P, L"abcabc", L"abc");
    ASSERT_PARSE_SUCCESS_VOID(P, L" abcabc", L" abcabc");
    ASSERT_PARSE_SUCCESS_VOID(P, L"abcab", L"ab");
    ASSERT_PARSE_SUCCESS_VOID(P, L"abc", L"");
    ASSERT_PARSE_SUCCESS_VOID(P, L"", L"");

    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabcabca"), e<int>("abcabca"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabca"), e<int>("abca"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabc"), e<int>("abc"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>(" abcabc"), e<int>(" abcabc"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcab"), e<int>("ab"));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abc"), e<int>(""));
    ASSERT_PARSE_SUCCESS_VOID(P, e<int>(""), e<int>(""));
}

} // namespace
} // namespace k3::tok3n::tests
