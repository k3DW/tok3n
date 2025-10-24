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
    ASSERT_PARSE_SUCCESS(Int1, " ", Class1(0), "");
    ASSERT_PARSE_FAILURE(Int1, "a");
    ASSERT_PARSE_SUCCESS(Int1, ".", Class1(1), "");
    ASSERT_PARSE_FAILURE(Int1, "");

    ASSERT_PARSE_SUCCESS(Int2, "abc.", Class2("abc", "."), "");
    ASSERT_PARSE_SUCCESS(Int2, "abc . ", Class2("abc", " "), ". ");
    ASSERT_PARSE_FAILURE(Int2, "");
    ASSERT_PARSE_FAILURE(Int2, "abc");

    ASSERT_PARSE_SUCCESS(Int3, "abc.", Class2("abc", "."), "");
    ASSERT_PARSE_SUCCESS(Int3, "abc . ", Class2("abc", " "), ". ");
    ASSERT_PARSE_FAILURE(Int3, "");
    ASSERT_PARSE_FAILURE(Int3, "abc");

    ASSERT_PARSE_SUCCESS(Int1, L" ", Class1(0), L"");
    ASSERT_PARSE_FAILURE(Int1, L"a");
    ASSERT_PARSE_SUCCESS(Int1, L".", Class1(1), L"");
    ASSERT_PARSE_FAILURE(Int1, L"");

    ASSERT_PARSE_SUCCESS(Int2, L"abc.", Class2(L"abc", L"."), L"");
    ASSERT_PARSE_SUCCESS(Int2, L"abc . ", Class2(L"abc", L" "), L". ");
    ASSERT_PARSE_FAILURE(Int2, L"");
    ASSERT_PARSE_FAILURE(Int2, L"abc");

    ASSERT_PARSE_SUCCESS(Int3, L"abc.", Class2(L"abc", L"."), L"");
    ASSERT_PARSE_SUCCESS(Int3, L"abc . ", Class2(L"abc", L" "), L". ");
    ASSERT_PARSE_FAILURE(Int3, L"");
    ASSERT_PARSE_FAILURE(Int3, L"abc");

    ASSERT_PARSE_SUCCESS(Int1, e<int>(" "), Class1(0), e<int>(""));
    ASSERT_PARSE_FAILURE(Int1, e<int>("a"));
    ASSERT_PARSE_SUCCESS(Int1, e<int>("."), Class1(1), e<int>(""));
    ASSERT_PARSE_FAILURE(Int1, e<int>(""));

    ASSERT_PARSE_SUCCESS(Int2, e<int>("abc."), Class2(e<int>("abc"), e<int>(".")), e<int>(""));
    ASSERT_PARSE_SUCCESS(Int2, e<int>("abc . "), Class2(e<int>("abc"), e<int>(" ")), e<int>(". "));
    ASSERT_PARSE_FAILURE(Int2, e<int>(""));
    ASSERT_PARSE_FAILURE(Int2, e<int>("abc"));

    ASSERT_PARSE_SUCCESS(Int3, e<int>("abc."), Class2(e<int>("abc"), e<int>(".")), e<int>(""));
    ASSERT_PARSE_SUCCESS(Int3, e<int>("abc . "), Class2(e<int>("abc"), e<int>(" ")), e<int>(". "));
    ASSERT_PARSE_FAILURE(Int3, e<int>(""));
    ASSERT_PARSE_FAILURE(Int3, e<int>("abc"));
}

TEST("into_parser", "Move only")
{
    {
        using T = MoveOnlyWrapper<output_span<char>>;
        using P = into_parser<ABC, T>;
        ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
        ASSERT_PARSE_FAILURE(P, "dcba");
        ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
    }

    {
        using T = MoveOnlyWrapper<output_span<wchar_t>>;
        using P = into_parser<ABC, T>;
        ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
        ASSERT_PARSE_FAILURE(P, L"dcba");
        ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
    }

    {
        using T = MoveOnlyWrapper<output_span<int>>;
        using P = into_parser<ABC, T>;
        ASSERT_PARSE_SUCCESS(P, e<int>("abcd"), T(e<int>("abc")), e<int>("d"));
        ASSERT_PARSE_FAILURE(P, e<int>("dcba"));
        ASSERT_PARSE_SUCCESS(P, e<int>("abcabcd"), T(e<int>("abc")), e<int>("abcd"));
    }
}

} // namespace
} // namespace k3::tok3n::tests
