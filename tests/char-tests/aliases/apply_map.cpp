// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("apply_map_parser");

TEST("apply_map_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Apm1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Apm2> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Apm1> | has_family<map_family>);
    EXPECT_THAT(the_parser<Apm2> | has_family<map_family>);

    EXPECT_THAT(the_parser<Apm1> | is_parser_for<char>.with_result<bool>);
    EXPECT_THAT(the_parser<Apm2> | is_parser_for<char>.with_result<std::size_t>);

    EXPECT_THAT(the_parser<Apm1> | is_parser_for<wchar_t>.with_result<bool>);
    EXPECT_THAT(the_parser<Apm2> | is_parser_for<wchar_t>.with_result<std::size_t>);

    EXPECT_THAT(the_parser<Apm1> | is_parser_for<int>.with_result<bool>);
    EXPECT_THAT(the_parser<Apm2> | is_parser_for<int>.with_result<std::size_t>);
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

} // namespace
} // namespace k3::tok3n::tests
