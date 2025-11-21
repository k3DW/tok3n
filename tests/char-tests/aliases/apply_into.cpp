// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("apply_into_parser");

TEST("apply_into_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Api1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Api2> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Api1> | has_family<map_family>);
    EXPECT_THAT(the_parser<Api2> | has_family<map_family>);

    EXPECT_THAT(the_parser<Api1> | is_parser_for<char>.with_result<Class2>);
    EXPECT_THAT(the_parser<Api2> | is_parser_for<char>.with_result<Class5>);

    EXPECT_THAT(the_parser<Api1> | is_parser_for<wchar_t>.with_result<Class2>);
    EXPECT_THAT(the_parser<Api2> | is_parser_for<wchar_t>.with_result<Class5>);

    EXPECT_THAT(the_parser<Api1> | is_parser_for<int>.with_result<Class2>);
    EXPECT_THAT(the_parser<Api2> | is_parser_for<int>.with_result<Class5>);
}

TEST("apply_into_parser", "Parse all")
{
    EXPECT_THAT(the_parser<Api1> | SUCCEEDS_PARSING("abc.", Class2("abc", "."), ""));
    EXPECT_THAT(the_parser<Api1> | SUCCEEDS_PARSING("abc . ", Class2("abc", " "), ". "));
    EXPECT_THAT(the_parser<Api1> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Api1> | FAILS_PARSING("abc"));

    EXPECT_THAT(the_parser<Api2> | SUCCEEDS_PARSING(".abc", Class5(".", "abc"), ""));
    EXPECT_THAT(the_parser<Api2> | SUCCEEDS_PARSING(" abc. ", Class5(" ", "abc"), ". "));
    EXPECT_THAT(the_parser<Api2> | FAILS_PARSING("."));
    EXPECT_THAT(the_parser<Api2> | FAILS_PARSING("abc"));

    EXPECT_THAT(the_parser<Api1> | SUCCEEDS_PARSING(L"abc.", Class2(L"abc", L"."), L""));
    EXPECT_THAT(the_parser<Api1> | SUCCEEDS_PARSING(L"abc . ", Class2(L"abc", L" "), L". "));
    EXPECT_THAT(the_parser<Api1> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Api1> | FAILS_PARSING(L"abc"));

    EXPECT_THAT(the_parser<Api2> | SUCCEEDS_PARSING(L".abc", Class5(L".", L"abc"), L""));
    EXPECT_THAT(the_parser<Api2> | SUCCEEDS_PARSING(L" abc. ", Class5(L" ", L"abc"), L". "));
    EXPECT_THAT(the_parser<Api2> | FAILS_PARSING(L"."));
    EXPECT_THAT(the_parser<Api2> | FAILS_PARSING(L"abc"));

    static constexpr auto arr_abc = e<int>("abc");
    static constexpr auto arr_dot = e<int>(".");
    static constexpr auto arr_space = e<int>(" ");

    EXPECT_THAT(the_parser<Api1> | SUCCEEDS_PARSING(e<int>("abc."), Class2(arr_abc, arr_dot), e<int>("")));
    EXPECT_THAT(the_parser<Api1> | SUCCEEDS_PARSING(e<int>("abc . "), Class2(arr_abc, arr_space), e<int>(". ")));
    EXPECT_THAT(the_parser<Api1> | FAILS_PARSING(e<int>("")));
    EXPECT_THAT(the_parser<Api1> | FAILS_PARSING(e<int>("abc")));

    EXPECT_THAT(the_parser<Api2> | SUCCEEDS_PARSING(e<int>(".abc"), Class5(arr_dot, arr_abc), e<int>("")));
    EXPECT_THAT(the_parser<Api2> | SUCCEEDS_PARSING(e<int>(" abc. "), Class5(arr_space, arr_abc), e<int>(". ")));
    EXPECT_THAT(the_parser<Api2> | FAILS_PARSING(e<int>(".")));
    EXPECT_THAT(the_parser<Api2> | FAILS_PARSING(e<int>("abc")));
}

TEST("apply_into_parser", "Move only")
{
    {
        using tuple = std::tuple<output_span<char>, output_span<char>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_into_parser<sequence_parser<Any3, ABC>, T>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("xabcd", T(std::tuple("x", "abc")), "d"));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING("ydcba"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("zabcabcd", T(std::tuple("z", "abc")), "abcd"));
    }

    {
        using tuple = std::tuple<output_span<wchar_t>, output_span<wchar_t>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_into_parser<sequence_parser<Any3, ABC>, T>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"xabcd", T(std::tuple(L"x", L"abc")), L"d"));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING(L"ydcba"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"zabcabcd", T(std::tuple(L"z", L"abc")), L"abcd"));
    }

    {
        using tuple = std::tuple<output_span<int>, output_span<int>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_into_parser<sequence_parser<Any3, ABC>, T>;
        static constexpr auto arr_abc = e<int>("abc");
        static constexpr auto arr_x = e<int>("x");
        static constexpr auto arr_z = e<int>("z");
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("xabcd"), T(tuple(arr_x, arr_abc)), e<int>("d")));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>("ydcba")));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("zabcabcd"), T(tuple(arr_z, arr_abc)), e<int>("abcd")));
    }
}

} // namespace
} // namespace k3::tok3n::tests
