// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("apply_map_parser");

TEST("apply_map_parser", "Requirements")
{
    ASSERT_PARSER_VALUE_TYPE(Apm1, value_type);
    ASSERT_PARSER_VALUE_TYPE(Apm2, value_type);

    ASSERT_IS_PARSER(Apm1, char, map_family, bool);
    ASSERT_IS_PARSER(Apm2, char, map_family, std::size_t);

    ASSERT_IS_PARSER(Apm1, wchar_t, map_family, bool);
    ASSERT_IS_PARSER(Apm2, wchar_t, map_family, std::size_t);

    ASSERT_IS_PARSER(Apm1, int, map_family, bool);
    ASSERT_IS_PARSER(Apm2, int, map_family, std::size_t);
}

TEST("apply_map_parser", "Parse all")
{
    ASSERT_PARSE_SUCCESS(Apm1, "abc???????", false, "?");
    ASSERT_PARSE_FAILURE(Apm1, "??abc???????");
    ASSERT_PARSE_SUCCESS(Apm1, "abc??abc???????", false, "abc???????");
    ASSERT_PARSE_SUCCESS(Apm1, "abc ??abc???????", true, " ??abc???????");
    ASSERT_PARSE_FAILURE(Apm1, "");

    ASSERT_PARSE_SUCCESS(Apm2, "abcabcabcabc??", 36, "");
    ASSERT_PARSE_SUCCESS(Apm2, "abcabcabcabc", 12, "");
    ASSERT_PARSE_SUCCESS(Apm2, "abcabcabcabc ??", 12, " ??");
    ASSERT_PARSE_SUCCESS(Apm2, "abc", 3, "");
    ASSERT_PARSE_FAILURE(Apm2, " abc");
    ASSERT_PARSE_FAILURE(Apm2, "");

    ASSERT_PARSE_SUCCESS(Apm1, L"abc???????", false, L"?");
    ASSERT_PARSE_FAILURE(Apm1, L"??abc???????");
    ASSERT_PARSE_SUCCESS(Apm1, L"abc??abc???????", false, L"abc???????");
    ASSERT_PARSE_SUCCESS(Apm1, L"abc ??abc???????", true, L" ??abc???????");
    ASSERT_PARSE_FAILURE(Apm1, L"");

    ASSERT_PARSE_SUCCESS(Apm2, L"abcabcabcabc??", 36, L"");
    ASSERT_PARSE_SUCCESS(Apm2, L"abcabcabcabc", 12, L"");
    ASSERT_PARSE_SUCCESS(Apm2, L"abcabcabcabc ??", 12, L" ??");
    ASSERT_PARSE_SUCCESS(Apm2, L"abc", 3, L"");
    ASSERT_PARSE_FAILURE(Apm2, L" abc");
    ASSERT_PARSE_FAILURE(Apm2, L"");

    ASSERT_PARSE_SUCCESS(Apm1, e<int>("abc???????"), false, e<int>("?"));
    ASSERT_PARSE_FAILURE(Apm1, e<int>("??abc???????"));
    ASSERT_PARSE_SUCCESS(Apm1, e<int>("abc??abc???????"), false, e<int>("abc???????"));
    ASSERT_PARSE_SUCCESS(Apm1, e<int>("abc ??abc???????"), true, e<int>(" ??abc???????"));
    ASSERT_PARSE_FAILURE(Apm1, e<int>(""));

    ASSERT_PARSE_SUCCESS(Apm2, e<int>("abcabcabcabc??"), 36, e<int>(""));
    ASSERT_PARSE_SUCCESS(Apm2, e<int>("abcabcabcabc"), 12, e<int>(""));
    ASSERT_PARSE_SUCCESS(Apm2, e<int>("abcabcabcabc ??"), 12, e<int>(" ??"));
    ASSERT_PARSE_SUCCESS(Apm2, e<int>("abc"), 3, e<int>(""));
    ASSERT_PARSE_FAILURE(Apm2, e<int>(" abc"));
    ASSERT_PARSE_FAILURE(Apm2, e<int>(""));
}

TEST("apply_map_parser", "Move only")
{
    {
        using tuple = std::tuple<output_span<char>, output_span<char>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_map_parser<sequence_parser<Any3, ABC>, integral_constant<T::make>>;
        ASSERT_PARSE_SUCCESS(P, "xabcd", T(std::tuple("x", "abc")), "d");
        ASSERT_PARSE_FAILURE(P, "ydcba");
        ASSERT_PARSE_SUCCESS(P, "zabcabcd", T(std::tuple("z", "abc")), "abcd");
    }

    {
        using tuple = std::tuple<output_span<wchar_t>, output_span<wchar_t>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_map_parser<sequence_parser<Any3, ABC>, integral_constant<T::make>>;
        ASSERT_PARSE_SUCCESS(P, L"xabcd", T(std::tuple(L"x", L"abc")), L"d");
        ASSERT_PARSE_FAILURE(P, L"ydcba");
        ASSERT_PARSE_SUCCESS(P, L"zabcabcd", T(std::tuple(L"z", L"abc")), L"abcd");
    }

    {
        using tuple = std::tuple<output_span<int>, output_span<int>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_map_parser<sequence_parser<Any3, ABC>, integral_constant<T::make>>;
        ASSERT_PARSE_SUCCESS(P, e<int>("xabcd"), T(std::tuple(e<int>("x"), e<int>("abc"))), e<int>("d"));
        ASSERT_PARSE_FAILURE(P, e<int>("ydcba"));
        ASSERT_PARSE_SUCCESS(P, e<int>("zabcabcd"), T(std::tuple(e<int>("z"), e<int>("abc"))), e<int>("abcd"));
    }
}
