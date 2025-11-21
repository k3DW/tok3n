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
    EXPECT_THAT(the_parser<TwoWay1> | SUCCEEDS_PARSING("abc", "ab", "c"));
    EXPECT_THAT(the_parser<TwoWay1> | SUCCEEDS_PARSING("ba", "b", "a"));
    EXPECT_THAT(the_parser<TwoWay1> | FAILS_PARSING("cba"));
    EXPECT_THAT(the_parser<TwoWay1> | FAILS_PARSING("dcba"));
    EXPECT_THAT(the_parser<TwoWay1> | SUCCEEDS_PARSING("edcba", "e", "dcba"));

    EXPECT_THAT(the_parser<TwoWay2> | SUCCEEDS_PARSING("abc", "a", "bc"));
    EXPECT_THAT(the_parser<TwoWay2> | SUCCEEDS_PARSING("ba", "b", "a"));
    EXPECT_THAT(the_parser<TwoWay2> | FAILS_PARSING("cba"));
    EXPECT_THAT(the_parser<TwoWay2> | FAILS_PARSING("dcba"));
    EXPECT_THAT(the_parser<TwoWay2> | SUCCEEDS_PARSING("edcba", "e", "dcba"));

    EXPECT_THAT(the_parser<TwoWay1> | SUCCEEDS_PARSING(L"abc", L"ab", L"c"));
    EXPECT_THAT(the_parser<TwoWay1> | SUCCEEDS_PARSING(L"ba", L"b", L"a"));
    EXPECT_THAT(the_parser<TwoWay1> | FAILS_PARSING(L"cba"));
    EXPECT_THAT(the_parser<TwoWay1> | FAILS_PARSING(L"dcba"));
    EXPECT_THAT(the_parser<TwoWay1> | SUCCEEDS_PARSING(L"edcba", L"e", L"dcba"));

    EXPECT_THAT(the_parser<TwoWay2> | SUCCEEDS_PARSING(L"abc", L"a", L"bc"));
    EXPECT_THAT(the_parser<TwoWay2> | SUCCEEDS_PARSING(L"ba", L"b", L"a"));
    EXPECT_THAT(the_parser<TwoWay2> | FAILS_PARSING(L"cba"));
    EXPECT_THAT(the_parser<TwoWay2> | FAILS_PARSING(L"dcba"));
    EXPECT_THAT(the_parser<TwoWay2> | SUCCEEDS_PARSING(L"edcba", L"e", L"dcba"));

    EXPECT_THAT(the_parser<TwoWay1> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("ab"), e<int>("c")));
    EXPECT_THAT(the_parser<TwoWay1> | SUCCEEDS_PARSING(e<int>("ba"), e<int>("b"), e<int>("a")));
    EXPECT_THAT(the_parser<TwoWay1> | FAILS_PARSING(e<int>("cba")));
    EXPECT_THAT(the_parser<TwoWay1> | FAILS_PARSING(e<int>("dcba")));
    EXPECT_THAT(the_parser<TwoWay1> | SUCCEEDS_PARSING(e<int>("edcba"), e<int>("e"), e<int>("dcba")));

    EXPECT_THAT(the_parser<TwoWay2> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("a"), e<int>("bc")));
    EXPECT_THAT(the_parser<TwoWay2> | SUCCEEDS_PARSING(e<int>("ba"), e<int>("b"), e<int>("a")));
    EXPECT_THAT(the_parser<TwoWay2> | FAILS_PARSING(e<int>("cba")));
    EXPECT_THAT(the_parser<TwoWay2> | FAILS_PARSING(e<int>("dcba")));
    EXPECT_THAT(the_parser<TwoWay2> | SUCCEEDS_PARSING(e<int>("edcba"), e<int>("e"), e<int>("dcba")));
}

TEST("choice_parser", "Parse three-way choice_parser")
{
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING("abc", "ab", "c"));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING("ba", "b", "a"));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING("cba", "c", "ba"));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING("dcba", "d", "cba"));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING("edcba", "e", "dcba"));

    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING("abc", "a", "bc"));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING("ba", "b", "a"));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING("cba", "c", "ba"));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING("dcba", "d", "cba"));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING("edcba", "e", "dcba"));

    EXPECT_THAT(the_parser<ThreeWay1> | FAILS_PARSING("zyx"));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING("xyz", "x", "yz"));
    EXPECT_THAT(the_parser<ThreeWay2> | FAILS_PARSING("zyx"));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING("xyz", "x", "yz"));

    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(L"abc", L"ab", L"c"));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(L"ba", L"b", L"a"));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(L"cba", L"c", L"ba"));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(L"dcba", L"d", L"cba"));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(L"edcba", L"e", L"dcba"));

    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(L"abc", L"a", L"bc"));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(L"ba", L"b", L"a"));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(L"cba", L"c", L"ba"));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(L"dcba", L"d", L"cba"));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(L"edcba", L"e", L"dcba"));

    EXPECT_THAT(the_parser<ThreeWay1> | FAILS_PARSING(L"zyx"));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(L"xyz", L"x", L"yz"));
    EXPECT_THAT(the_parser<ThreeWay2> | FAILS_PARSING(L"zyx"));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(L"xyz", L"x", L"yz"));

    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("ab"), e<int>("c")));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(e<int>("ba"), e<int>("b"), e<int>("a")));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(e<int>("cba"), e<int>("c"), e<int>("ba")));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(e<int>("dcba"), e<int>("d"), e<int>("cba")));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(e<int>("edcba"), e<int>("e"), e<int>("dcba")));

    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("a"), e<int>("bc")));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(e<int>("ba"), e<int>("b"), e<int>("a")));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(e<int>("cba"), e<int>("c"), e<int>("ba")));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(e<int>("dcba"), e<int>("d"), e<int>("cba")));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(e<int>("edcba"), e<int>("e"), e<int>("dcba")));

    EXPECT_THAT(the_parser<ThreeWay1> | FAILS_PARSING(e<int>("zyx")));
    EXPECT_THAT(the_parser<ThreeWay1> | SUCCEEDS_PARSING(e<int>("xyz"), e<int>("x"), e<int>("yz")));
    EXPECT_THAT(the_parser<ThreeWay2> | FAILS_PARSING(e<int>("zyx")));
    EXPECT_THAT(the_parser<ThreeWay2> | SUCCEEDS_PARSING(e<int>("xyz"), e<int>("x"), e<int>("yz")));
}

TEST("choice_parser", "Parse void result_type")
{
    EXPECT_THAT(the_parser<Cho5> | FAILS_PARSING("ab"));
    ASSERT_PARSE_SUCCESS_VOID(Cho5, "abca", "a");
    ASSERT_PARSE_SUCCESS_VOID(Cho5, "abcabcabc", "abcabc");

    EXPECT_THAT(the_parser<Cho5> | FAILS_PARSING(L"ab"));
    ASSERT_PARSE_SUCCESS_VOID(Cho5, L"abca", L"a");
    ASSERT_PARSE_SUCCESS_VOID(Cho5, L"abcabcabc", L"abcabc");

    EXPECT_THAT(the_parser<Cho5> | FAILS_PARSING(e<int>("ab")));
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
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("xyz", T("x"), "yz"));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING("abxyz"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcxyz", T("abc"), "xyz"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("zabcxyz", T("z"), "abcxyz"));
    }

    {
        using T = MoveOnlyWrapper<output_span<wchar_t>>;
        using P = choice_parser<into_parser<Any3, T>, into_parser<ABC, T>>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"xyz", T(L"x"), L"yz"));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING(L"abxyz"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcxyz", T(L"abc"), L"xyz"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"zabcxyz", T(L"z"), L"abcxyz"));
    }

    {
        using T = MoveOnlyWrapper<output_span<int>>;
        using P = choice_parser<into_parser<Any3, T>, into_parser<ABC, T>>;
        static constexpr auto arr_abc = e<int>("abc");
        static constexpr auto arr_x = e<int>("x");
        static constexpr auto arr_z = e<int>("z");
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("xyz"), T(arr_x), e<int>("yz")));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>("abxyz")));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcxyz"), T(arr_abc), e<int>("xyz")));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("zabcxyz"), T(arr_z), e<int>("abcxyz")));
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
