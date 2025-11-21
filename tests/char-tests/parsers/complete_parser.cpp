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

FIXTURE("complete_parser");

TEST("complete_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Com1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Com2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Com3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Com4> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Com5> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Com6> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Com7> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Com1> | has_family<complete_family>);
    EXPECT_THAT(the_parser<Com2> | has_family<complete_family>);
    EXPECT_THAT(the_parser<Com3> | has_family<complete_family>);
    EXPECT_THAT(the_parser<Com4> | has_family<complete_family>);
    EXPECT_THAT(the_parser<Com5> | has_family<complete_family>);
    EXPECT_THAT(the_parser<Com6> | has_family<complete_family>);
    EXPECT_THAT(the_parser<Com7> | has_family<complete_family>);

    EXPECT_THAT(the_parser<Com1> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Com2> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Com3> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Com4> | (is_parser_for<char>.with_result<std::tuple<output_span<char>, output_span<char>>>));
    EXPECT_THAT(the_parser<Com5> | (is_parser_for<char>.with_result<std::optional<std::tuple<output_span<char>, output_span<char>>>>));
    EXPECT_THAT(the_parser<Com6> | (is_parser_for<char>.with_result<std::vector<std::tuple<output_span<char>, output_span<char>>>>));
    EXPECT_THAT(the_parser<Com7> | (is_parser_for<char>.with_result<std::vector<std::tuple<output_span<char>, output_span<char>>>>));

    EXPECT_THAT(the_parser<Com1> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Com2> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Com3> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Com4> | (is_parser_for<wchar_t>.with_result<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>));
    EXPECT_THAT(the_parser<Com5> | (is_parser_for<wchar_t>.with_result<std::optional<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>>));
    EXPECT_THAT(the_parser<Com6> | (is_parser_for<wchar_t>.with_result<std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>>));
    EXPECT_THAT(the_parser<Com7> | (is_parser_for<wchar_t>.with_result<std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>>));

    EXPECT_THAT(the_parser<Com1> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Com2> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Com3> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Com4> | (is_parser_for<int>.with_result<std::tuple<output_span<int>, output_span<int>>>));
    EXPECT_THAT(the_parser<Com5> | (is_parser_for<int>.with_result<std::optional<std::tuple<output_span<int>, output_span<int>>>>));
    EXPECT_THAT(the_parser<Com6> | (is_parser_for<int>.with_result<std::vector<std::tuple<output_span<int>, output_span<int>>>>));
    EXPECT_THAT(the_parser<Com7> | (is_parser_for<int>.with_result<std::vector<std::tuple<output_span<int>, output_span<int>>>>));
}

TEST("complete_parser", "complete_parser<all_of_parser>")
{
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING("litera"));
    EXPECT_THAT(the_parser<Com1> | SUCCEEDS_PARSING("literal", "literal", ""));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING("literally"));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING("literallitera"));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING("literalliterallitera"));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(" literalliterallitera"));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(L"litera"));
    EXPECT_THAT(the_parser<Com1> | SUCCEEDS_PARSING(L"literal", L"literal", L""));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(L"literally"));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(L"literallitera"));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(L"literalliterallitera"));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(L" literalliterallitera"));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(e<int>("litera")));
    EXPECT_THAT(the_parser<Com1> | SUCCEEDS_PARSING(e<int>("literal"), e<int>("literal"), e<int>()));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(e<int>("literally")));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(e<int>("literallitera")));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(e<int>("literalliterallitera")));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(e<int>(" literalliterallitera")));
    EXPECT_THAT(the_parser<Com1> | FAILS_PARSING(e<int>()));
}
TEST("complete_parser", "complete_parser<any_of_parser>")
{
    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING("a", "a", ""));
    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING("b", "b", ""));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING("abcdef"));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING("fedcba"));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING("cbabcccbjklmnop"));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING(L"a", L"a", L""));
    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING(L"b", L"b", L""));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING(L"abcdef"));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING(L"fedcba"));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING(L"cbabcccbjklmnop"));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING(e<int>("a"), e<int>("a"), e<int>()));
    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING(e<int>("b"), e<int>("b"), e<int>()));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING(e<int>("abcdef")));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING(e<int>("fedcba")));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING(e<int>("cbabcccbjklmnop")));
    EXPECT_THAT(the_parser<Com2> | FAILS_PARSING(e<int>()));
}
TEST("complete_parser", "complete_parser<choice_parser>")
{
    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING("abliteralcbliteralcf"));
    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING("abliteralcblitralcf"));
    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING("literalabacliteral"));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING("literal", "literal", ""));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING("a", "a", ""));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING("b", "b", ""));
    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING(L"abliteralcbliteralcf"));
    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING(L"abliteralcblitralcf"));
    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING(L"literalabacliteral"));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(L"literal", L"literal", L""));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(L"a", L"a", L""));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(L"b", L"b", L""));
    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING(e<int>("abliteralcbliteralcf")));
    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING(e<int>("abliteralcblitralcf")));
    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING(e<int>("literalabacliteral")));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(e<int>("literal"), e<int>("literal"), e<int>()));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(e<int>("a"), e<int>("a"), e<int>()));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(e<int>("b"), e<int>("b"), e<int>()));
    EXPECT_THAT(the_parser<Com3> | FAILS_PARSING(e<int>()));
}
TEST("complete_parser", "complete_parser<sequence_parser>")
{
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING("literalaliteralcliteralcliteralb"));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING("literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING("literala", std::tuple("literal", "a"), ""));
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING("literalb", std::tuple("literal", "b"), ""));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING("literald"));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING("aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(L"literalaliteralcliteralcliteralb"));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(L"literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING(L"literala", std::tuple(L"literal", L"a"), L""));
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING(L"literalb", std::tuple(L"literal", L"b"), L""));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(L"literald"));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(L"aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(e<int>("literalaliteralcliteralcliteralb")));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(e<int>("literalaliteralcliteralcliteralbliteral")));
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING(e<int>("literala"), std::tuple(e<int>("literal"), e<int>("a")), e<int>()));
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING(e<int>("literalb"), std::tuple(e<int>("literal"), e<int>("b")), e<int>()));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(e<int>("literald")));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(e<int>("aliteralaliteralcliteralbliteral")));
    EXPECT_THAT(the_parser<Com4> | FAILS_PARSING(e<int>()));
}
TEST("complete_parser", "complete_parser<maybe_parser>")
{
    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING("literalaliteralcliteralcliteralb"));
    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING("literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING("literala", std::optional(std::tuple("literal", "a")), ""));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING("literalb", std::optional(std::tuple("literal", "b")), ""));
    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING("literald"));
    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING("aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING("", std::nullopt, ""));

    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING(L"literalaliteralcliteralcliteralb"));
    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING(L"literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(L"literala", std::optional(std::tuple(L"literal", L"a")), L""));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(L"literalb", std::optional(std::tuple(L"literal", L"b")), L""));
    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING(L"literald"));
    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING(L"aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(L"", std::nullopt, L""));

    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING(e<int>("literalaliteralcliteralcliteralb")));
    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING(e<int>("literalaliteralcliteralcliteralbliteral")));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(e<int>("literala"), std::optional(std::tuple(e<int>("literal"), e<int>("a"))), e<int>()));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(e<int>("literalb"), std::optional(std::tuple(e<int>("literal"), e<int>("b"))), e<int>()));
    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING(e<int>("literald")));
    EXPECT_THAT(the_parser<Com5> | FAILS_PARSING(e<int>("aliteralaliteralcliteralbliteral")));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(e<int>(), std::nullopt, e<int>()));
}
TEST("complete_parser", "complete_parser<one_or_more_parser>")
{
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralb", Com6::result_for<char>({ { "literal", "a" }, { "literal", "c" }, { "literal", "c" }, { "literal", "b" } }), ""));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING("literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING("literala", Com6::result_for<char>({ { "literal", "a" } }), ""));
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING("literalb", Com6::result_for<char>({ { "literal", "b" } }), ""));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING("literald"));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING("aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralb", Com6::result_for<wchar_t>({ { L"literal", L"a" }, { L"literal", L"c" }, { L"literal", L"c" }, { L"literal", L"b" } }), L""));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING(L"literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(L"literala", Com6::result_for<wchar_t>({ { L"literal", L"a" } }), L""));
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(L"literalb", Com6::result_for<wchar_t>({ { L"literal", L"b" } }), L""));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING(L"literald"));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING(L"aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralb"), Com6::result_for<int>({ { arr_literal, arr_a }, { arr_literal, arr_c }, { arr_literal, arr_c }, { arr_literal, arr_b } }), e<int>()));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING(e<int>("literalaliteralcliteralcliteralbliteral")));
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(e<int>("literala"), Com6::result_for<int>({ { arr_literal, arr_a } }), e<int>()));
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(e<int>("literalb"), Com6::result_for<int>({ { arr_literal, arr_b } }), e<int>()));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING(e<int>("literald")));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING(e<int>("aliteralaliteralcliteralbliteral")));
    EXPECT_THAT(the_parser<Com6> | FAILS_PARSING(e<int>()));
}
TEST("complete_parser", "complete_parser<zero_or_more_parser>")
{
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralb", Com7::result_for<char>({ { "literal", "a" }, { "literal", "c" }, { "literal", "c" }, { "literal", "b" } }), ""));
    EXPECT_THAT(the_parser<Com7> | FAILS_PARSING("literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING("literala", Com7::result_for<char>({ { "literal", "a" } }), ""));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING("literalb", Com7::result_for<char>({ { "literal", "b" } }), ""));
    EXPECT_THAT(the_parser<Com7> | FAILS_PARSING("literald"));
    EXPECT_THAT(the_parser<Com7> | FAILS_PARSING("aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING("", Com7::result_for<char>{}, ""));

    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralb", Com7::result_for<wchar_t>({ { L"literal", L"a" }, { L"literal", L"c" }, { L"literal", L"c" }, { L"literal", L"b" } }), L""));
    EXPECT_THAT(the_parser<Com7> | FAILS_PARSING(L"literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(L"literala", Com7::result_for<wchar_t>({ { L"literal", L"a" } }), L""));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(L"literalb", Com7::result_for<wchar_t>({ { L"literal", L"b" } }), L""));
    EXPECT_THAT(the_parser<Com7> | FAILS_PARSING(L"literald"));
    EXPECT_THAT(the_parser<Com7> | FAILS_PARSING(L"aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(L"", Com7::result_for<wchar_t>{}, L""));

    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralb"), Com7::result_for<int>({ { arr_literal, arr_a }, { arr_literal, arr_c }, { arr_literal, arr_c }, { arr_literal, arr_b } }), e<int>()));
    EXPECT_THAT(the_parser<Com7> | FAILS_PARSING(e<int>("literalaliteralcliteralcliteralbliteral")));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(e<int>("literala"), Com7::result_for<int>({ { arr_literal, arr_a } }), e<int>()));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(e<int>("literalb"), Com7::result_for<int>({ { arr_literal, arr_b } }), e<int>()));
    EXPECT_THAT(the_parser<Com7> | FAILS_PARSING(e<int>("literald")));
    EXPECT_THAT(the_parser<Com7> | FAILS_PARSING(e<int>("aliteralaliteralcliteralbliteral")));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(e<int>(), Com7::result_for<int>{}, e<int>()));
}

} // namespace
} // namespace k3::tok3n::tests
