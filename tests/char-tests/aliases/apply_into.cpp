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

    ASSERT_IS_PARSER(Api1, char, map_family, Class2);
    ASSERT_IS_PARSER(Api2, char, map_family, Class5);

    ASSERT_IS_PARSER(Api1, wchar_t, map_family, Class2);
    ASSERT_IS_PARSER(Api2, wchar_t, map_family, Class5);

    ASSERT_IS_PARSER(Api1, int, map_family, Class2);
    ASSERT_IS_PARSER(Api2, int, map_family, Class5);
}

TEST("apply_into_parser", "Parse all")
{
    ASSERT_PARSE_SUCCESS(Api1, "abc.", Class2("abc", "."), "");
    ASSERT_PARSE_SUCCESS(Api1, "abc . ", Class2("abc", " "), ". ");
    ASSERT_PARSE_FAILURE(Api1, "");
    ASSERT_PARSE_FAILURE(Api1, "abc");

    ASSERT_PARSE_SUCCESS(Api2, ".abc", Class5(".", "abc"), "");
    ASSERT_PARSE_SUCCESS(Api2, " abc. ", Class5(" ", "abc"), ". ");
    ASSERT_PARSE_FAILURE(Api2, ".");
    ASSERT_PARSE_FAILURE(Api2, "abc");

    ASSERT_PARSE_SUCCESS(Api1, L"abc.", Class2(L"abc", L"."), L"");
    ASSERT_PARSE_SUCCESS(Api1, L"abc . ", Class2(L"abc", L" "), L". ");
    ASSERT_PARSE_FAILURE(Api1, L"");
    ASSERT_PARSE_FAILURE(Api1, L"abc");

    ASSERT_PARSE_SUCCESS(Api2, L".abc", Class5(L".", L"abc"), L"");
    ASSERT_PARSE_SUCCESS(Api2, L" abc. ", Class5(L" ", L"abc"), L". ");
    ASSERT_PARSE_FAILURE(Api2, L".");
    ASSERT_PARSE_FAILURE(Api2, L"abc");

    ASSERT_PARSE_SUCCESS(Api1, e<int>("abc."), Class2(e<int>("abc"), e<int>(".")), e<int>(""));
    ASSERT_PARSE_SUCCESS(Api1, e<int>("abc . "), Class2(e<int>("abc"), e<int>(" ")), e<int>(". "));
    ASSERT_PARSE_FAILURE(Api1, e<int>(""));
    ASSERT_PARSE_FAILURE(Api1, e<int>("abc"));

    ASSERT_PARSE_SUCCESS(Api2, e<int>(".abc"), Class5(e<int>("."), e<int>("abc")), e<int>(""));
    ASSERT_PARSE_SUCCESS(Api2, e<int>(" abc. "), Class5(e<int>(" "), e<int>("abc")), e<int>(". "));
    ASSERT_PARSE_FAILURE(Api2, e<int>("."));
    ASSERT_PARSE_FAILURE(Api2, e<int>("abc"));
}

TEST("apply_into_parser", "Move only")
{
    {
        using tuple = std::tuple<output_span<char>, output_span<char>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_into_parser<sequence_parser<Any3, ABC>, T>;
        ASSERT_PARSE_SUCCESS(P, "xabcd", T(std::tuple("x", "abc")), "d");
        ASSERT_PARSE_FAILURE(P, "ydcba");
        ASSERT_PARSE_SUCCESS(P, "zabcabcd", T(std::tuple("z", "abc")), "abcd");
    }

    {
        using tuple = std::tuple<output_span<wchar_t>, output_span<wchar_t>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_into_parser<sequence_parser<Any3, ABC>, T>;
        ASSERT_PARSE_SUCCESS(P, L"xabcd", T(std::tuple(L"x", L"abc")), L"d");
        ASSERT_PARSE_FAILURE(P, L"ydcba");
        ASSERT_PARSE_SUCCESS(P, L"zabcabcd", T(std::tuple(L"z", L"abc")), L"abcd");
    }

    {
        using tuple = std::tuple<output_span<int>, output_span<int>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_into_parser<sequence_parser<Any3, ABC>, T>;
        ASSERT_PARSE_SUCCESS(P, e<int>("xabcd"), T(std::tuple(e<int>("x"), e<int>("abc"))), e<int>("d"));
        ASSERT_PARSE_FAILURE(P, e<int>("ydcba"));
        ASSERT_PARSE_SUCCESS(P, e<int>("zabcabcd"), T(std::tuple(e<int>("z"), e<int>("abc"))), e<int>("abcd"));
    }
}

} // namespace
} // namespace k3::tok3n::tests
