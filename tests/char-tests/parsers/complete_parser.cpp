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
    ASSERT_PARSE_FAILURE(Com1, "litera");
    EXPECT_THAT(the_parser<Com1> | SUCCEEDS_PARSING("literal", "literal", ""));
    ASSERT_PARSE_FAILURE(Com1, "literally");
    ASSERT_PARSE_FAILURE(Com1, "literallitera");
    ASSERT_PARSE_FAILURE(Com1, "literalliterallitera");
    ASSERT_PARSE_FAILURE(Com1, " literalliterallitera");
    ASSERT_PARSE_FAILURE(Com1, "");

    ASSERT_PARSE_FAILURE(Com1, L"litera");
    EXPECT_THAT(the_parser<Com1> | SUCCEEDS_PARSING(L"literal", L"literal", L""));
    ASSERT_PARSE_FAILURE(Com1, L"literally");
    ASSERT_PARSE_FAILURE(Com1, L"literallitera");
    ASSERT_PARSE_FAILURE(Com1, L"literalliterallitera");
    ASSERT_PARSE_FAILURE(Com1, L" literalliterallitera");
    ASSERT_PARSE_FAILURE(Com1, L"");

    ASSERT_PARSE_FAILURE(Com1, e<int>("litera"));
    EXPECT_THAT(the_parser<Com1> | SUCCEEDS_PARSING(e<int>("literal"), e<int>("literal"), e<int>()));
    ASSERT_PARSE_FAILURE(Com1, e<int>("literally"));
    ASSERT_PARSE_FAILURE(Com1, e<int>("literallitera"));
    ASSERT_PARSE_FAILURE(Com1, e<int>("literalliterallitera"));
    ASSERT_PARSE_FAILURE(Com1, e<int>(" literalliterallitera"));
    ASSERT_PARSE_FAILURE(Com1, e<int>());
}
TEST("complete_parser", "complete_parser<any_of_parser>")
{
    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING("a", "a", ""));
    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING("b", "b", ""));
    ASSERT_PARSE_FAILURE(Com2, "abcdef");
    ASSERT_PARSE_FAILURE(Com2, "fedcba");
    ASSERT_PARSE_FAILURE(Com2, "cbabcccbjklmnop");
    ASSERT_PARSE_FAILURE(Com2, "");

    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING(L"a", L"a", L""));
    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING(L"b", L"b", L""));
    ASSERT_PARSE_FAILURE(Com2, L"abcdef");
    ASSERT_PARSE_FAILURE(Com2, L"fedcba");
    ASSERT_PARSE_FAILURE(Com2, L"cbabcccbjklmnop");
    ASSERT_PARSE_FAILURE(Com2, L"");

    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING(e<int>("a"), e<int>("a"), e<int>()));
    EXPECT_THAT(the_parser<Com2> | SUCCEEDS_PARSING(e<int>("b"), e<int>("b"), e<int>()));
    ASSERT_PARSE_FAILURE(Com2, e<int>("abcdef"));
    ASSERT_PARSE_FAILURE(Com2, e<int>("fedcba"));
    ASSERT_PARSE_FAILURE(Com2, e<int>("cbabcccbjklmnop"));
    ASSERT_PARSE_FAILURE(Com2, e<int>());
}
TEST("complete_parser", "complete_parser<choice_parser>")
{
    ASSERT_PARSE_FAILURE(Com3, "abliteralcbliteralcf");
    ASSERT_PARSE_FAILURE(Com3, "abliteralcblitralcf");
    ASSERT_PARSE_FAILURE(Com3, "literalabacliteral");
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING("literal", "literal", ""));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING("a", "a", ""));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING("b", "b", ""));
    ASSERT_PARSE_FAILURE(Com3, "");

    ASSERT_PARSE_FAILURE(Com3, L"abliteralcbliteralcf");
    ASSERT_PARSE_FAILURE(Com3, L"abliteralcblitralcf");
    ASSERT_PARSE_FAILURE(Com3, L"literalabacliteral");
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(L"literal", L"literal", L""));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(L"a", L"a", L""));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(L"b", L"b", L""));
    ASSERT_PARSE_FAILURE(Com3, L"");

    ASSERT_PARSE_FAILURE(Com3, e<int>("abliteralcbliteralcf"));
    ASSERT_PARSE_FAILURE(Com3, e<int>("abliteralcblitralcf"));
    ASSERT_PARSE_FAILURE(Com3, e<int>("literalabacliteral"));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(e<int>("literal"), e<int>("literal"), e<int>()));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(e<int>("a"), e<int>("a"), e<int>()));
    EXPECT_THAT(the_parser<Com3> | SUCCEEDS_PARSING(e<int>("b"), e<int>("b"), e<int>()));
    ASSERT_PARSE_FAILURE(Com3, e<int>());
}
TEST("complete_parser", "complete_parser<sequence_parser>")
{
    ASSERT_PARSE_FAILURE(Com4, "literalaliteralcliteralcliteralb");
    ASSERT_PARSE_FAILURE(Com4, "literalaliteralcliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING("literala", std::tuple("literal", "a"), ""));
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING("literalb", std::tuple("literal", "b"), ""));
    ASSERT_PARSE_FAILURE(Com4, "literald");
    ASSERT_PARSE_FAILURE(Com4, "aliteralaliteralcliteralbliteral");
    ASSERT_PARSE_FAILURE(Com4, "");

    ASSERT_PARSE_FAILURE(Com4, L"literalaliteralcliteralcliteralb");
    ASSERT_PARSE_FAILURE(Com4, L"literalaliteralcliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING(L"literala", std::tuple(L"literal", L"a"), L""));
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING(L"literalb", std::tuple(L"literal", L"b"), L""));
    ASSERT_PARSE_FAILURE(Com4, L"literald");
    ASSERT_PARSE_FAILURE(Com4, L"aliteralaliteralcliteralbliteral");
    ASSERT_PARSE_FAILURE(Com4, L"");

    ASSERT_PARSE_FAILURE(Com4, e<int>("literalaliteralcliteralcliteralb"));
    ASSERT_PARSE_FAILURE(Com4, e<int>("literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING(e<int>("literala"), std::tuple(e<int>("literal"), e<int>("a")), e<int>()));
    EXPECT_THAT(the_parser<Com4> | SUCCEEDS_PARSING(e<int>("literalb"), std::tuple(e<int>("literal"), e<int>("b")), e<int>()));
    ASSERT_PARSE_FAILURE(Com4, e<int>("literald"));
    ASSERT_PARSE_FAILURE(Com4, e<int>("aliteralaliteralcliteralbliteral"));
    ASSERT_PARSE_FAILURE(Com4, e<int>());
}
TEST("complete_parser", "complete_parser<maybe_parser>")
{
    ASSERT_PARSE_FAILURE(Com5, "literalaliteralcliteralcliteralb");
    ASSERT_PARSE_FAILURE(Com5, "literalaliteralcliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING("literala", std::optional(std::tuple("literal", "a")), ""));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING("literalb", std::optional(std::tuple("literal", "b")), ""));
    ASSERT_PARSE_FAILURE(Com5, "literald");
    ASSERT_PARSE_FAILURE(Com5, "aliteralaliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING("", std::nullopt, ""));

    ASSERT_PARSE_FAILURE(Com5, L"literalaliteralcliteralcliteralb");
    ASSERT_PARSE_FAILURE(Com5, L"literalaliteralcliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(L"literala", std::optional(std::tuple(L"literal", L"a")), L""));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(L"literalb", std::optional(std::tuple(L"literal", L"b")), L""));
    ASSERT_PARSE_FAILURE(Com5, L"literald");
    ASSERT_PARSE_FAILURE(Com5, L"aliteralaliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(L"", std::nullopt, L""));

    ASSERT_PARSE_FAILURE(Com5, e<int>("literalaliteralcliteralcliteralb"));
    ASSERT_PARSE_FAILURE(Com5, e<int>("literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(e<int>("literala"), std::optional(std::tuple(e<int>("literal"), e<int>("a"))), e<int>()));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(e<int>("literalb"), std::optional(std::tuple(e<int>("literal"), e<int>("b"))), e<int>()));
    ASSERT_PARSE_FAILURE(Com5, e<int>("literald"));
    ASSERT_PARSE_FAILURE(Com5, e<int>("aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com5> | SUCCEEDS_PARSING(e<int>(), std::nullopt, e<int>()));
}
TEST("complete_parser", "complete_parser<one_or_more_parser>")
{
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralb", Com6::result_for<char>({ { "literal", "a" }, { "literal", "c" }, { "literal", "c" }, { "literal", "b" } }), ""));
    ASSERT_PARSE_FAILURE(Com6, "literalaliteralcliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING("literala", Com6::result_for<char>({ { "literal", "a" } }), ""));
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING("literalb", Com6::result_for<char>({ { "literal", "b" } }), ""));
    ASSERT_PARSE_FAILURE(Com6, "literald");
    ASSERT_PARSE_FAILURE(Com6, "aliteralaliteralcliteralbliteral");
    ASSERT_PARSE_FAILURE(Com6, "");

    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralb", Com6::result_for<wchar_t>({ { L"literal", L"a" }, { L"literal", L"c" }, { L"literal", L"c" }, { L"literal", L"b" } }), L""));
    ASSERT_PARSE_FAILURE(Com6, L"literalaliteralcliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(L"literala", Com6::result_for<wchar_t>({ { L"literal", L"a" } }), L""));
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(L"literalb", Com6::result_for<wchar_t>({ { L"literal", L"b" } }), L""));
    ASSERT_PARSE_FAILURE(Com6, L"literald");
    ASSERT_PARSE_FAILURE(Com6, L"aliteralaliteralcliteralbliteral");
    ASSERT_PARSE_FAILURE(Com6, L"");

    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralb"), Com6::result_for<int>({ { arr_literal, arr_a }, { arr_literal, arr_c }, { arr_literal, arr_c }, { arr_literal, arr_b } }), e<int>()));
    ASSERT_PARSE_FAILURE(Com6, e<int>("literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(e<int>("literala"), Com6::result_for<int>({ { arr_literal, arr_a } }), e<int>()));
    EXPECT_THAT(the_parser<Com6> | SUCCEEDS_PARSING(e<int>("literalb"), Com6::result_for<int>({ { arr_literal, arr_b } }), e<int>()));
    ASSERT_PARSE_FAILURE(Com6, e<int>("literald"));
    ASSERT_PARSE_FAILURE(Com6, e<int>("aliteralaliteralcliteralbliteral"));
    ASSERT_PARSE_FAILURE(Com6, e<int>());
}
TEST("complete_parser", "complete_parser<zero_or_more_parser>")
{
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING("literalaliteralcliteralcliteralb", Com7::result_for<char>({ { "literal", "a" }, { "literal", "c" }, { "literal", "c" }, { "literal", "b" } }), ""));
    ASSERT_PARSE_FAILURE(Com7, "literalaliteralcliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING("literala", Com7::result_for<char>({ { "literal", "a" } }), ""));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING("literalb", Com7::result_for<char>({ { "literal", "b" } }), ""));
    ASSERT_PARSE_FAILURE(Com7, "literald");
    ASSERT_PARSE_FAILURE(Com7, "aliteralaliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING("", Com7::result_for<char>{}, ""));

    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(L"literalaliteralcliteralcliteralb", Com7::result_for<wchar_t>({ { L"literal", L"a" }, { L"literal", L"c" }, { L"literal", L"c" }, { L"literal", L"b" } }), L""));
    ASSERT_PARSE_FAILURE(Com7, L"literalaliteralcliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(L"literala", Com7::result_for<wchar_t>({ { L"literal", L"a" } }), L""));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(L"literalb", Com7::result_for<wchar_t>({ { L"literal", L"b" } }), L""));
    ASSERT_PARSE_FAILURE(Com7, L"literald");
    ASSERT_PARSE_FAILURE(Com7, L"aliteralaliteralcliteralbliteral");
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(L"", Com7::result_for<wchar_t>{}, L""));

    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(e<int>("literalaliteralcliteralcliteralb"), Com7::result_for<int>({ { arr_literal, arr_a }, { arr_literal, arr_c }, { arr_literal, arr_c }, { arr_literal, arr_b } }), e<int>()));
    ASSERT_PARSE_FAILURE(Com7, e<int>("literalaliteralcliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(e<int>("literala"), Com7::result_for<int>({ { arr_literal, arr_a } }), e<int>()));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(e<int>("literalb"), Com7::result_for<int>({ { arr_literal, arr_b } }), e<int>()));
    ASSERT_PARSE_FAILURE(Com7, e<int>("literald"));
    ASSERT_PARSE_FAILURE(Com7, e<int>("aliteralaliteralcliteralbliteral"));
    EXPECT_THAT(the_parser<Com7> | SUCCEEDS_PARSING(e<int>(), Com7::result_for<int>{}, e<int>()));
}

} // namespace
} // namespace k3::tok3n::tests
