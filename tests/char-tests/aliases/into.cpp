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
    ASSERT_PARSE_FAILURE(Int1, "a");
    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(".", Class1(1), ""));
    ASSERT_PARSE_FAILURE(Int1, "");

    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING("abc.", Class2("abc", "."), ""));
    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING("abc . ", Class2("abc", " "), ". "));
    ASSERT_PARSE_FAILURE(Int2, "");
    ASSERT_PARSE_FAILURE(Int2, "abc");

    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING("abc.", Class2("abc", "."), ""));
    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING("abc . ", Class2("abc", " "), ". "));
    ASSERT_PARSE_FAILURE(Int3, "");
    ASSERT_PARSE_FAILURE(Int3, "abc");

    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(L" ", Class1(0), L""));
    ASSERT_PARSE_FAILURE(Int1, L"a");
    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(L".", Class1(1), L""));
    ASSERT_PARSE_FAILURE(Int1, L"");

    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING(L"abc.", Class2(L"abc", L"."), L""));
    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING(L"abc . ", Class2(L"abc", L" "), L". "));
    ASSERT_PARSE_FAILURE(Int2, L"");
    ASSERT_PARSE_FAILURE(Int2, L"abc");

    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING(L"abc.", Class2(L"abc", L"."), L""));
    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING(L"abc . ", Class2(L"abc", L" "), L". "));
    ASSERT_PARSE_FAILURE(Int3, L"");
    ASSERT_PARSE_FAILURE(Int3, L"abc");

    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(e<int>(" "), Class1(0), e<int>("")));
    ASSERT_PARSE_FAILURE(Int1, e<int>("a"));
    EXPECT_THAT(the_parser<Int1> | SUCCEEDS_PARSING(e<int>("."), Class1(1), e<int>("")));
    ASSERT_PARSE_FAILURE(Int1, e<int>(""));

    static constexpr auto arr_abc = e<int>("abc");
    static constexpr auto arr_dot = e<int>(".");
    static constexpr auto arr_space = e<int>(" ");

    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING(e<int>("abc."), Class2(arr_abc, arr_dot), e<int>("")));
    EXPECT_THAT(the_parser<Int2> | SUCCEEDS_PARSING(e<int>("abc . "), Class2(arr_abc, arr_space), e<int>(". ")));
    ASSERT_PARSE_FAILURE(Int2, e<int>(""));
    ASSERT_PARSE_FAILURE(Int2, e<int>("abc"));

    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING(e<int>("abc."), Class2(arr_abc, arr_dot), e<int>("")));
    EXPECT_THAT(the_parser<Int3> | SUCCEEDS_PARSING(e<int>("abc . "), Class2(arr_abc, arr_space), e<int>(". ")));
    ASSERT_PARSE_FAILURE(Int3, e<int>(""));
    ASSERT_PARSE_FAILURE(Int3, e<int>("abc"));
}

TEST("into_parser", "Move only")
{
    {
        using T = MoveOnlyWrapper<output_span<char>>;
        using P = into_parser<ABC, T>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcd", T("abc"), "d"));
        ASSERT_PARSE_FAILURE(P, "dcba");
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcabcd", T("abc"), "abcd"));
    }

    {
        using T = MoveOnlyWrapper<output_span<wchar_t>>;
        using P = into_parser<ABC, T>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcd", T(L"abc"), L"d"));
        ASSERT_PARSE_FAILURE(P, L"dcba");
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcabcd", T(L"abc"), L"abcd"));
    }

    {
        using T = MoveOnlyWrapper<output_span<int>>;
        using P = into_parser<ABC, T>;
        static constexpr auto arr_abc = e<int>("abc");
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcd"), T(arr_abc), e<int>("d")));
        ASSERT_PARSE_FAILURE(P, e<int>("dcba"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcabcd"), T(arr_abc), e<int>("abcd")));
    }
}

} // namespace
} // namespace k3::tok3n::tests
