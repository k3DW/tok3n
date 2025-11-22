// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("into_parser");

TEST("into_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Int1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Int2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Int3> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Int1> | has_family<map_family>);
    EXPECT_THAT(the_parser<Int2> | has_family<map_family>);
    EXPECT_THAT(the_parser<Int3> | has_family<map_family>);

    EXPECT_THAT(the_parser<Int1> | is_parser_for<char>.with_result<Class1>);
    EXPECT_THAT(the_parser<Int2> | is_parser_for<char>.with_result<Class2>);
    EXPECT_THAT(the_parser<Int3> | is_parser_for<char>.with_result<Class2>);

    EXPECT_THAT(the_parser<Int1> | is_parser_for<wchar_t>.with_result<Class1>);
    EXPECT_THAT(the_parser<Int2> | is_parser_for<wchar_t>.with_result<Class2>);
    EXPECT_THAT(the_parser<Int3> | is_parser_for<wchar_t>.with_result<Class2>);

    EXPECT_THAT(the_parser<Int1> | is_parser_for<int>.with_result<Class1>);
    EXPECT_THAT(the_parser<Int2> | is_parser_for<int>.with_result<Class2>);
    EXPECT_THAT(the_parser<Int3> | is_parser_for<int>.with_result<Class2>);
}

TEST("into_parser", "Parse all")
{
    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(" ", Class1(0), ""));
    EXPECT_THAT(the_parser<Int1> | FAILS_PARSING("a"));
    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(".", Class1(1), ""));
    EXPECT_THAT(the_parser<Int1> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING("abc.", Class2("abc", "."), ""));
    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING("abc . ", Class2("abc", " "), ". "));
    EXPECT_THAT(the_parser<Int2> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Int2> | FAILS_PARSING("abc"));

    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING("abc.", Class2("abc", "."), ""));
    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING("abc . ", Class2("abc", " "), ". "));
    EXPECT_THAT(the_parser<Int3> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Int3> | FAILS_PARSING("abc"));

    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(L" ", Class1(0), L""));
    EXPECT_THAT(the_parser<Int1> | FAILS_PARSING(L"a"));
    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(L".", Class1(1), L""));
    EXPECT_THAT(the_parser<Int1> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING(L"abc.", Class2(L"abc", L"."), L""));
    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING(L"abc . ", Class2(L"abc", L" "), L". "));
    EXPECT_THAT(the_parser<Int2> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Int2> | FAILS_PARSING(L"abc"));

    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING(L"abc.", Class2(L"abc", L"."), L""));
    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING(L"abc . ", Class2(L"abc", L" "), L". "));
    EXPECT_THAT(the_parser<Int3> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Int3> | FAILS_PARSING(L"abc"));

    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(e<int>(" "), Class1(0), e<int>("")));
    EXPECT_THAT(the_parser<Int1> | FAILS_PARSING(e<int>("a")));
    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(e<int>("."), Class1(1), e<int>("")));
    EXPECT_THAT(the_parser<Int1> | FAILS_PARSING(e<int>("")));

    static constexpr auto arr_abc = e<int>("abc");
    static constexpr auto arr_dot = e<int>(".");
    static constexpr auto arr_space = e<int>(" ");

    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING(e<int>("abc."), Class2(arr_abc, arr_dot), e<int>("")));
    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING(e<int>("abc . "), Class2(arr_abc, arr_space), e<int>(". ")));
    EXPECT_THAT(the_parser<Int2> | FAILS_PARSING(e<int>("")));
    EXPECT_THAT(the_parser<Int2> | FAILS_PARSING(e<int>("abc")));

    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING(e<int>("abc."), Class2(arr_abc, arr_dot), e<int>("")));
    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING(e<int>("abc . "), Class2(arr_abc, arr_space), e<int>(". ")));
    EXPECT_THAT(the_parser<Int3> | FAILS_PARSING(e<int>("")));
    EXPECT_THAT(the_parser<Int3> | FAILS_PARSING(e<int>("abc")));
}

TEST("into_parser", "Move only")
{
    {
        using T = MoveOnlyWrapper<output_span<char>>;
        using P = into_parser<ABC, T>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcd", T("abc"), "d"));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING("dcba"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcabcd", T("abc"), "abcd"));
    }

    {
        using T = MoveOnlyWrapper<output_span<wchar_t>>;
        using P = into_parser<ABC, T>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcd", T(L"abc"), L"d"));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING(L"dcba"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcabcd", T(L"abc"), L"abcd"));
    }

    {
        using T = MoveOnlyWrapper<output_span<int>>;
        using P = into_parser<ABC, T>;
        static constexpr auto arr_abc = e<int>("abc");
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcd"), T(arr_abc), e<int>("d")));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>("dcba")));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcabcd"), T(arr_abc), e<int>("abcd")));
    }
}

} // namespace
} // namespace k3::tok3n::tests
