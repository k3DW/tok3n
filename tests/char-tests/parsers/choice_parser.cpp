// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

using TwoWay1 = Cho1;
using TwoWay2 = Cho2;

using ThreeWay1 = Cho3;
using ThreeWay2 = Cho4;

FIXTURE("choice_parser");

TEST("choice_parser", "Requirements")
{
    EXPECT_THAT(the_parser<TwoWay1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<TwoWay2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<ThreeWay1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<ThreeWay2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Cho5> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<TwoWay1> | has_family<choice_family>);
    EXPECT_THAT(the_parser<TwoWay2> | has_family<choice_family>);
    EXPECT_THAT(the_parser<ThreeWay1> | has_family<choice_family>);
    EXPECT_THAT(the_parser<ThreeWay2> | has_family<choice_family>);
    EXPECT_THAT(the_parser<Cho5> | has_family<choice_family>);

    EXPECT_THAT(the_parser<TwoWay1> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<TwoWay2> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<ThreeWay1> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<ThreeWay2> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Cho5> | is_parser_for<char>.with_result<void>);

    EXPECT_THAT(the_parser<TwoWay1> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<TwoWay2> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<ThreeWay1> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<ThreeWay2> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Cho5> | is_parser_for<wchar_t>.with_result<void>);

    EXPECT_THAT(the_parser<TwoWay1> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<TwoWay2> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<ThreeWay1> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<ThreeWay2> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Cho5> | is_parser_for<int>.with_result<void>);
}

TEST("choice_parser", "Parse two-way choice_parser")
{
    ASSERT_PARSE_SUCCESS(TwoWay1, "abc", "ab", "c");
    ASSERT_PARSE_SUCCESS(TwoWay1, "ba", "b", "a");
    ASSERT_PARSE_FAILURE(TwoWay1, "cba");
    ASSERT_PARSE_FAILURE(TwoWay1, "dcba");
    ASSERT_PARSE_SUCCESS(TwoWay1, "edcba", "e", "dcba");

    ASSERT_PARSE_SUCCESS(TwoWay2, "abc", "a", "bc");
    ASSERT_PARSE_SUCCESS(TwoWay2, "ba", "b", "a");
    ASSERT_PARSE_FAILURE(TwoWay2, "cba");
    ASSERT_PARSE_FAILURE(TwoWay2, "dcba");
    ASSERT_PARSE_SUCCESS(TwoWay2, "edcba", "e", "dcba");

    ASSERT_PARSE_SUCCESS(TwoWay1, L"abc", L"ab", L"c");
    ASSERT_PARSE_SUCCESS(TwoWay1, L"ba", L"b", L"a");
    ASSERT_PARSE_FAILURE(TwoWay1, L"cba");
    ASSERT_PARSE_FAILURE(TwoWay1, L"dcba");
    ASSERT_PARSE_SUCCESS(TwoWay1, L"edcba", L"e", L"dcba");

    ASSERT_PARSE_SUCCESS(TwoWay2, L"abc", L"a", L"bc");
    ASSERT_PARSE_SUCCESS(TwoWay2, L"ba", L"b", L"a");
    ASSERT_PARSE_FAILURE(TwoWay2, L"cba");
    ASSERT_PARSE_FAILURE(TwoWay2, L"dcba");
    ASSERT_PARSE_SUCCESS(TwoWay2, L"edcba", L"e", L"dcba");

    ASSERT_PARSE_SUCCESS(TwoWay1, e<int>("abc"), e<int>("ab"), e<int>("c"));
    ASSERT_PARSE_SUCCESS(TwoWay1, e<int>("ba"), e<int>("b"), e<int>("a"));
    ASSERT_PARSE_FAILURE(TwoWay1, e<int>("cba"));
    ASSERT_PARSE_FAILURE(TwoWay1, e<int>("dcba"));
    ASSERT_PARSE_SUCCESS(TwoWay1, e<int>("edcba"), e<int>("e"), e<int>("dcba"));

    ASSERT_PARSE_SUCCESS(TwoWay2, e<int>("abc"), e<int>("a"), e<int>("bc"));
    ASSERT_PARSE_SUCCESS(TwoWay2, e<int>("ba"), e<int>("b"), e<int>("a"));
    ASSERT_PARSE_FAILURE(TwoWay2, e<int>("cba"));
    ASSERT_PARSE_FAILURE(TwoWay2, e<int>("dcba"));
    ASSERT_PARSE_SUCCESS(TwoWay2, e<int>("edcba"), e<int>("e"), e<int>("dcba"));
}

TEST("choice_parser", "Parse three-way choice_parser")
{
    ASSERT_PARSE_SUCCESS(ThreeWay1, "abc", "ab", "c");
    ASSERT_PARSE_SUCCESS(ThreeWay1, "ba", "b", "a");
    ASSERT_PARSE_SUCCESS(ThreeWay1, "cba", "c", "ba");
    ASSERT_PARSE_SUCCESS(ThreeWay1, "dcba", "d", "cba");
    ASSERT_PARSE_SUCCESS(ThreeWay1, "edcba", "e", "dcba");

    ASSERT_PARSE_SUCCESS(ThreeWay2, "abc", "a", "bc");
    ASSERT_PARSE_SUCCESS(ThreeWay2, "ba", "b", "a");
    ASSERT_PARSE_SUCCESS(ThreeWay2, "cba", "c", "ba");
    ASSERT_PARSE_SUCCESS(ThreeWay2, "dcba", "d", "cba");
    ASSERT_PARSE_SUCCESS(ThreeWay2, "edcba", "e", "dcba");

    ASSERT_PARSE_FAILURE(ThreeWay1, "zyx");
    ASSERT_PARSE_SUCCESS(ThreeWay1, "xyz", "x", "yz");
    ASSERT_PARSE_FAILURE(ThreeWay2, "zyx");
    ASSERT_PARSE_SUCCESS(ThreeWay2, "xyz", "x", "yz");

    ASSERT_PARSE_SUCCESS(ThreeWay1, L"abc", L"ab", L"c");
    ASSERT_PARSE_SUCCESS(ThreeWay1, L"ba", L"b", L"a");
    ASSERT_PARSE_SUCCESS(ThreeWay1, L"cba", L"c", L"ba");
    ASSERT_PARSE_SUCCESS(ThreeWay1, L"dcba", L"d", L"cba");
    ASSERT_PARSE_SUCCESS(ThreeWay1, L"edcba", L"e", L"dcba");

    ASSERT_PARSE_SUCCESS(ThreeWay2, L"abc", L"a", L"bc");
    ASSERT_PARSE_SUCCESS(ThreeWay2, L"ba", L"b", L"a");
    ASSERT_PARSE_SUCCESS(ThreeWay2, L"cba", L"c", L"ba");
    ASSERT_PARSE_SUCCESS(ThreeWay2, L"dcba", L"d", L"cba");
    ASSERT_PARSE_SUCCESS(ThreeWay2, L"edcba", L"e", L"dcba");

    ASSERT_PARSE_FAILURE(ThreeWay1, L"zyx");
    ASSERT_PARSE_SUCCESS(ThreeWay1, L"xyz", L"x", L"yz");
    ASSERT_PARSE_FAILURE(ThreeWay2, L"zyx");
    ASSERT_PARSE_SUCCESS(ThreeWay2, L"xyz", L"x", L"yz");

    ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("abc"), e<int>("ab"), e<int>("c"));
    ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("ba"), e<int>("b"), e<int>("a"));
    ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("cba"), e<int>("c"), e<int>("ba"));
    ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("dcba"), e<int>("d"), e<int>("cba"));
    ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("edcba"), e<int>("e"), e<int>("dcba"));

    ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("abc"), e<int>("a"), e<int>("bc"));
    ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("ba"), e<int>("b"), e<int>("a"));
    ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("cba"), e<int>("c"), e<int>("ba"));
    ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("dcba"), e<int>("d"), e<int>("cba"));
    ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("edcba"), e<int>("e"), e<int>("dcba"));

    ASSERT_PARSE_FAILURE(ThreeWay1, e<int>("zyx"));
    ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("xyz"), e<int>("x"), e<int>("yz"));
    ASSERT_PARSE_FAILURE(ThreeWay2, e<int>("zyx"));
    ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("xyz"), e<int>("x"), e<int>("yz"));
}

TEST("choice_parser", "Parse void result_type")
{
    ASSERT_PARSE_FAILURE(Cho5, "ab");
    ASSERT_PARSE_SUCCESS_VOID(Cho5, "abca", "a");
    ASSERT_PARSE_SUCCESS_VOID(Cho5, "abcabcabc", "abcabc");

    ASSERT_PARSE_FAILURE(Cho5, L"ab");
    ASSERT_PARSE_SUCCESS_VOID(Cho5, L"abca", L"a");
    ASSERT_PARSE_SUCCESS_VOID(Cho5, L"abcabcabc", L"abcabc");

    ASSERT_PARSE_FAILURE(Cho5, e<int>("ab"));
    ASSERT_PARSE_SUCCESS_VOID(Cho5, e<int>("abca"), e<int>("a"));
    ASSERT_PARSE_SUCCESS_VOID(Cho5, e<int>("abcabcabc"), e<int>("abcabc"));
}



TEST("choice_parser", "Constructible not only from parsers with the same result_type")
{
    EXPECT_THAT((the_parser_family<choice_parser>.is_valid_with<Any1, Any3, Non2, Non1, All2>));
    EXPECT_THAT((the_parser_family<choice_parser>.is_valid_with<Any1, sequence_parser<Any2, Any3>>));
}

TEST("choice_parser", "Not constructible empty")
{
    EXPECT_THAT(the_parser_family<choice_parser>.is_not_valid_with<>);
}



TEST("choice_parser", "Move only")
{
    {
        using T = MoveOnlyWrapper<output_span<char>>;
        using P = choice_parser<into_parser<Any3, T>, into_parser<ABC, T>>;
        ASSERT_PARSE_SUCCESS(P, "xyz", T("x"), "yz");
        ASSERT_PARSE_FAILURE(P, "abxyz");
        ASSERT_PARSE_SUCCESS(P, "abcxyz", T("abc"), "xyz");
        ASSERT_PARSE_SUCCESS(P, "zabcxyz", T("z"), "abcxyz");
    }

    {
        using T = MoveOnlyWrapper<output_span<wchar_t>>;
        using P = choice_parser<into_parser<Any3, T>, into_parser<ABC, T>>;
        ASSERT_PARSE_SUCCESS(P, L"xyz", T(L"x"), L"yz");
        ASSERT_PARSE_FAILURE(P, L"abxyz");
        ASSERT_PARSE_SUCCESS(P, L"abcxyz", T(L"abc"), L"xyz");
        ASSERT_PARSE_SUCCESS(P, L"zabcxyz", T(L"z"), L"abcxyz");
    }

    {
        using T = MoveOnlyWrapper<output_span<int>>;
        using P = choice_parser<into_parser<Any3, T>, into_parser<ABC, T>>;
        ASSERT_PARSE_SUCCESS(P, e<int>("xyz"), T(e<int>("x")), e<int>("yz"));
        ASSERT_PARSE_FAILURE(P, e<int>("abxyz"));
        ASSERT_PARSE_SUCCESS(P, e<int>("abcxyz"), T(e<int>("abc")), e<int>("xyz"));
        ASSERT_PARSE_SUCCESS(P, e<int>("zabcxyz"), T(e<int>("z")), e<int>("abcxyz"));
    }
}

TEST("choice_parser", "Result type")
{
    using C1 = constant_parser<SpaceDot, integral_constant<0>>;
    using C2 = constant_parser<SpaceDot, integral_constant<1>>;

    using P1 = choice_parser<ABC, QQ, SpaceDot>;
    EXPECT_THAT(the_parser<P1> | has_family<choice_family>);
    EXPECT_THAT(the_parser<P1> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<P1> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<P1> | is_parser_for<int>.with_result<output_span<int>>);

    using P2 = choice_parser<ABC, C1, QQ>;
    EXPECT_THAT(the_parser<P2> | has_family<choice_family>);
    EXPECT_THAT(the_parser<P2> | (is_parser_for<char>.with_result<std::variant<output_span<char>, int>>));
    EXPECT_THAT(the_parser<P2> | (is_parser_for<wchar_t>.with_result<std::variant<output_span<wchar_t>, int>>));
    EXPECT_THAT(the_parser<P2> | (is_parser_for<int>.with_result<std::variant<output_span<int>, int>>));

    using P3 = choice_parser<ABC, QQ, C1>;
    EXPECT_THAT(the_parser<P3> | has_family<choice_family>);
    EXPECT_THAT(the_parser<P3> | (is_parser_for<char>.with_result<std::variant<output_span<char>, int>>));
    EXPECT_THAT(the_parser<P3> | (is_parser_for<wchar_t>.with_result<std::variant<output_span<wchar_t>, int>>));
    EXPECT_THAT(the_parser<P3> | (is_parser_for<int>.with_result<std::variant<output_span<int>, int>>));

    using P4 = choice_parser<C1, ABC, QQ>;
    EXPECT_THAT(the_parser<P4> | has_family<choice_family>);
    EXPECT_THAT(the_parser<P4> | (is_parser_for<char>.with_result<std::variant<int, output_span<char>>>));
    EXPECT_THAT(the_parser<P4> | (is_parser_for<wchar_t>.with_result<std::variant<int, output_span<wchar_t>>>));
    EXPECT_THAT(the_parser<P4> | (is_parser_for<int>.with_result<std::variant<int, output_span<int>>>));

    using P5 = choice_parser<C1, ABC, QQ, C2>;
    EXPECT_THAT(the_parser<P5> | has_family<choice_family>);
    EXPECT_THAT(the_parser<P5> | (is_parser_for<char>.with_result<std::variant<int, output_span<char>>>));
    EXPECT_THAT(the_parser<P5> | (is_parser_for<wchar_t>.with_result<std::variant<int, output_span<wchar_t>>>));
    EXPECT_THAT(the_parser<P5> | (is_parser_for<int>.with_result<std::variant<int, output_span<int>>>));

    using P6 = choice_parser<C1, ABC, C2, QQ>;
    EXPECT_THAT(the_parser<P6> | has_family<choice_family>);
    EXPECT_THAT(the_parser<P6> | (is_parser_for<char>.with_result<std::variant<int, output_span<char>>>));
    EXPECT_THAT(the_parser<P6> | (is_parser_for<wchar_t>.with_result<std::variant<int, output_span<wchar_t>>>));
    EXPECT_THAT(the_parser<P6> | (is_parser_for<int>.with_result<std::variant<int, output_span<int>>>));
}

} // namespace
} // namespace k3::tok3n::tests
