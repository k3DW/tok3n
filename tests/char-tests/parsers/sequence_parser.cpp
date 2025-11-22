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
    EXPECT_THAT(the_parser<TwoWay> | FAILS_PARSING("abc"));
    EXPECT_THAT(the_parser<TwoWay> | FAILS_PARSING("abcd"));
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING("abef", std::tuple("ab", "e"), "f"));
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING("ab ef", std::tuple("ab", " "), "ef"));

    EXPECT_THAT(the_parser<TwoWay> | FAILS_PARSING(L"abc"));
    EXPECT_THAT(the_parser<TwoWay> | FAILS_PARSING(L"abcd"));
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING(L"abef", std::tuple(L"ab", L"e"), L"f"));
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING(L"ab ef", std::tuple(L"ab", L" "), L"ef"));

    EXPECT_THAT(the_parser<TwoWay> | FAILS_PARSING(e<int>("abc")));
    EXPECT_THAT(the_parser<TwoWay> | FAILS_PARSING(e<int>("abcd")));
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING(e<int>("abef"), std::tuple(e<int>("ab"), e<int>("e")), e<int>("f")));
    EXPECT_THAT(the_parser<TwoWay> | SUCCEEDS_PARSING(e<int>("ab ef"), std::tuple(e<int>("ab"), e<int>(" ")), e<int>("ef")));
}

TEST("sequence_parser", "Parse three-way sequence_parser")
{
    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING("abcde", std::tuple("ab", "c", "d"), "e"));
    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING("abdc", std::tuple("ab", "d", "c"), ""));
    EXPECT_THAT(the_parser<ThreeWay> | FAILS_PARSING("abcz"));

    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING(L"abcde", std::tuple(L"ab", L"c", L"d"), L"e"));
    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING(L"abdc", std::tuple(L"ab", L"d", L"c"), L""));
    EXPECT_THAT(the_parser<ThreeWay> | FAILS_PARSING(L"abcz"));

    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING(e<int>("abcde"), std::tuple(e<int>("ab"), e<int>("c"), e<int>("d")), e<int>("e")));
    EXPECT_THAT(the_parser<ThreeWay> | SUCCEEDS_PARSING(e<int>("abdc"), std::tuple(e<int>("ab"), e<int>("d"), e<int>("c")), e<int>()));
    EXPECT_THAT(the_parser<ThreeWay> | FAILS_PARSING(e<int>("abcz")));
}

TEST("sequence_parser", "Parse void result_type")
{
    EXPECT_THAT(the_parser<Seq5> | FAILS_PARSING("ab"));
    EXPECT_THAT(the_parser<Seq5> | FAILS_PARSING("abca"));
    EXPECT_THAT(the_parser<Seq5> | SUCCEEDS_PARSING_VOID("abcabcabcdabcd", "dabcd"));

    EXPECT_THAT(the_parser<Seq5> | FAILS_PARSING(L"ab"));
    EXPECT_THAT(the_parser<Seq5> | FAILS_PARSING(L"abca"));
    EXPECT_THAT(the_parser<Seq5> | SUCCEEDS_PARSING_VOID(L"abcabcabcdabcd", L"dabcd"));

    EXPECT_THAT(the_parser<Seq5> | FAILS_PARSING(e<int>("ab")));
    EXPECT_THAT(the_parser<Seq5> | FAILS_PARSING(e<int>("abca")));
    EXPECT_THAT(the_parser<Seq5> | SUCCEEDS_PARSING_VOID(e<int>("abcabcabcdabcd"), e<int>("dabcd")));
}



TEST("sequence_parser", "Not constructible empty")
{
    EXPECT_THAT(the_parser_family<sequence_parser>.is_not_valid_with<>);
}



TEST("sequence_parser", "sequence_parser<ignore_parser>")
{
    using P = sequence_parser<ABC, ignore_parser<QQ>, ABC>;

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abc??abc??", std::tuple("abc", "abc"), "??"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING("abcabc??"));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abc??abc??", std::tuple(L"abc", L"abc"), L"??"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L"abcabc??"));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abc??abc??"), std::tuple(e<int>("abc"), e<int>("abc")), e<int>("??")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>("abcabc??")));
}

} // namespace
} // namespace k3::tok3n::tests
