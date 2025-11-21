// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

using TwoWay = Seq1;
using ThreeWay = Seq3;

FIXTURE("sequence_parser");

TEST("sequence_parser", "Requirements")
{
    EXPECT_THAT(the_parser<TwoWay> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<ThreeWay> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Seq5> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<TwoWay> | has_family<sequence_family>);
    EXPECT_THAT(the_parser<ThreeWay> | has_family<sequence_family>);
    EXPECT_THAT(the_parser<Seq5> | has_family<sequence_family>);

    EXPECT_THAT(the_parser<TwoWay> | (is_parser_for<char>.with_result<std::tuple<output_span<char>, output_span<char>>>));
    EXPECT_THAT(the_parser<ThreeWay> | (is_parser_for<char>.with_result<std::tuple<output_span<char>, output_span<char>, output_span<char>>>));
    EXPECT_THAT(the_parser<Seq5> | is_parser_for<char>.with_result<void>);

    EXPECT_THAT(the_parser<TwoWay> | (is_parser_for<wchar_t>.with_result<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>));
    EXPECT_THAT(the_parser<ThreeWay> | (is_parser_for<wchar_t>.with_result<std::tuple<output_span<wchar_t>, output_span<wchar_t>, output_span<wchar_t>>>));
    EXPECT_THAT(the_parser<Seq5> | is_parser_for<wchar_t>.with_result<void>);

    EXPECT_THAT(the_parser<TwoWay> | (is_parser_for<int>.with_result<std::tuple<output_span<int>, output_span<int>>>));
    EXPECT_THAT(the_parser<ThreeWay> | (is_parser_for<int>.with_result<std::tuple<output_span<int>, output_span<int>, output_span<int>>>));
    EXPECT_THAT(the_parser<Seq5> | is_parser_for<int>.with_result<void>);
}

TEST("sequence_parser", "Parse two-way sequence_parser")
{
    ASSERT_PARSE_FAILURE(TwoWay, "abc");
    ASSERT_PARSE_FAILURE(TwoWay, "abcd");
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING("abef", std::tuple("ab", "e"), "f"));
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING("ab ef", std::tuple("ab", " "), "ef"));

    ASSERT_PARSE_FAILURE(TwoWay, L"abc");
    ASSERT_PARSE_FAILURE(TwoWay, L"abcd");
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING(L"abef", std::tuple(L"ab", L"e"), L"f"));
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING(L"ab ef", std::tuple(L"ab", L" "), L"ef"));

    ASSERT_PARSE_FAILURE(TwoWay, e<int>("abc"));
    ASSERT_PARSE_FAILURE(TwoWay, e<int>("abcd"));
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING(e<int>("abef"), std::tuple(e<int>("ab"), e<int>("e")), e<int>("f")));
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING(e<int>("ab ef"), std::tuple(e<int>("ab"), e<int>(" ")), e<int>("ef")));
}

TEST("sequence_parser", "Parse three-way sequence_parser")
{
    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING("abcde", std::tuple("ab", "c", "d"), "e"));
    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING("abdc", std::tuple("ab", "d", "c"), ""));
    ASSERT_PARSE_FAILURE(ThreeWay, "abcz");

    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING(L"abcde", std::tuple(L"ab", L"c", L"d"), L"e"));
    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING(L"abdc", std::tuple(L"ab", L"d", L"c"), L""));
    ASSERT_PARSE_FAILURE(ThreeWay, L"abcz");

    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING(e<int>("abcde"), std::tuple(e<int>("ab"), e<int>("c"), e<int>("d")), e<int>("e")));
    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING(e<int>("abdc"), std::tuple(e<int>("ab"), e<int>("d"), e<int>("c")), e<int>()));
    ASSERT_PARSE_FAILURE(ThreeWay, e<int>("abcz"));
}

TEST("sequence_parser", "Parse void result_type")
{
    ASSERT_PARSE_FAILURE(Seq5, "ab");
    ASSERT_PARSE_FAILURE(Seq5, "abca");
    ASSERT_PARSE_SUCCESS_VOID(Seq5, "abcabcabcdabcd", "dabcd");

    ASSERT_PARSE_FAILURE(Seq5, L"ab");
    ASSERT_PARSE_FAILURE(Seq5, L"abca");
    ASSERT_PARSE_SUCCESS_VOID(Seq5, L"abcabcabcdabcd", L"dabcd");

    ASSERT_PARSE_FAILURE(Seq5, e<int>("ab"));
    ASSERT_PARSE_FAILURE(Seq5, e<int>("abca"));
    ASSERT_PARSE_SUCCESS_VOID(Seq5, e<int>("abcabcabcdabcd"), e<int>("dabcd"));
}



TEST("sequence_parser", "Not constructible empty")
{
    EXPECT_THAT(the_parser_family<sequence_parser>.is_not_valid_with<>);
}



TEST("sequence_parser", "sequence_parser<ignore_parser>")
{
    using P = sequence_parser<ABC, ignore_parser<QQ>, ABC>;

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abc??abc??", std::tuple("abc", "abc"), "??"));
    ASSERT_PARSE_FAILURE(P, "abcabc??");

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abc??abc??", std::tuple(L"abc", L"abc"), L"??"));
    ASSERT_PARSE_FAILURE(P, L"abcabc??");

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abc??abc??"), std::tuple(e<int>("abc"), e<int>("abc")), e<int>("??")));
    ASSERT_PARSE_FAILURE(P, e<int>("abcabc??"));
}

} // namespace
} // namespace k3::tok3n::tests
