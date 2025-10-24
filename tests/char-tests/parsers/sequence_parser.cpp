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

    ASSERT_IS_PARSER(TwoWay, char, sequence_family, std::tuple<output_span<char>, output_span<char>>);
    ASSERT_IS_PARSER(ThreeWay, char, sequence_family, std::tuple<output_span<char>, output_span<char>, output_span<char>>);
    ASSERT_IS_PARSER(Seq5, char, sequence_family, void);

    ASSERT_IS_PARSER(TwoWay, wchar_t, sequence_family, std::tuple<output_span<wchar_t>, output_span<wchar_t>>);
    ASSERT_IS_PARSER(ThreeWay, wchar_t, sequence_family, std::tuple<output_span<wchar_t>, output_span<wchar_t>, output_span<wchar_t>>);
    ASSERT_IS_PARSER(Seq5, wchar_t, sequence_family, void);

    ASSERT_IS_PARSER(TwoWay, int, sequence_family, std::tuple<output_span<int>, output_span<int>>);
    ASSERT_IS_PARSER(ThreeWay, int, sequence_family, std::tuple<output_span<int>, output_span<int>, output_span<int>>);
    ASSERT_IS_PARSER(Seq5, int, sequence_family, void);
}

TEST("sequence_parser", "Parse two-way sequence_parser")
{
    ASSERT_PARSE_FAILURE(TwoWay, "abc");
    ASSERT_PARSE_FAILURE(TwoWay, "abcd");
    ASSERT_PARSE_SUCCESS(TwoWay, "abef", std::tuple("ab", "e"), "f");
    ASSERT_PARSE_SUCCESS(TwoWay, "ab ef", std::tuple("ab", " "), "ef");

    ASSERT_PARSE_FAILURE(TwoWay, L"abc");
    ASSERT_PARSE_FAILURE(TwoWay, L"abcd");
    ASSERT_PARSE_SUCCESS(TwoWay, L"abef", std::tuple(L"ab", L"e"), L"f");
    ASSERT_PARSE_SUCCESS(TwoWay, L"ab ef", std::tuple(L"ab", L" "), L"ef");

    ASSERT_PARSE_FAILURE(TwoWay, e<int>("abc"));
    ASSERT_PARSE_FAILURE(TwoWay, e<int>("abcd"));
    ASSERT_PARSE_SUCCESS(TwoWay, e<int>("abef"), std::tuple(e<int>("ab"), e<int>("e")), e<int>("f"));
    ASSERT_PARSE_SUCCESS(TwoWay, e<int>("ab ef"), std::tuple(e<int>("ab"), e<int>(" ")), e<int>("ef"));
}

TEST("sequence_parser", "Parse three-way sequence_parser")
{
    ASSERT_PARSE_SUCCESS(ThreeWay, "abcde", std::tuple("ab", "c", "d"), "e");
    ASSERT_PARSE_SUCCESS(ThreeWay, "abdc", std::tuple("ab", "d", "c"), "");
    ASSERT_PARSE_FAILURE(ThreeWay, "abcz");

    ASSERT_PARSE_SUCCESS(ThreeWay, L"abcde", std::tuple(L"ab", L"c", L"d"), L"e");
    ASSERT_PARSE_SUCCESS(ThreeWay, L"abdc", std::tuple(L"ab", L"d", L"c"), L"");
    ASSERT_PARSE_FAILURE(ThreeWay, L"abcz");

    ASSERT_PARSE_SUCCESS(ThreeWay, e<int>("abcde"), std::tuple(e<int>("ab"), e<int>("c"), e<int>("d")), e<int>("e"));
    ASSERT_PARSE_SUCCESS(ThreeWay, e<int>("abdc"), std::tuple(e<int>("ab"), e<int>("d"), e<int>("c")), e<int>());
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
    ASSERT_PARSER_NOT_CONSTRUCTIBLE(sequence_parser);
}



TEST("sequence_parser", "sequence_parser<ignore_parser>")
{
    using P = sequence_parser<ABC, ignore_parser<QQ>, ABC>;

    ASSERT_PARSE_SUCCESS(P, "abc??abc??", std::tuple("abc", "abc"), "??");
    ASSERT_PARSE_FAILURE(P, "abcabc??");

    ASSERT_PARSE_SUCCESS(P, L"abc??abc??", std::tuple(L"abc", L"abc"), L"??");
    ASSERT_PARSE_FAILURE(P, L"abcabc??");

    ASSERT_PARSE_SUCCESS(P, e<int>("abc??abc??"), std::tuple(e<int>("abc"), e<int>("abc")), e<int>("??"));
    ASSERT_PARSE_FAILURE(P, e<int>("abcabc??"));
}

} // namespace
} // namespace k3::tok3n::tests
