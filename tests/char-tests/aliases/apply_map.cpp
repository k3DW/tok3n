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
    EXPECT_THAT(the_parser<Apm1> | SUCCEEDS_PARSING("abc???????", false, "?"));
    EXPECT_THAT(the_parser<Apm1> | FAILS_PARSING("??abc???????"));
    EXPECT_THAT(the_parser<Apm1> | SUCCEEDS_PARSING("abc??abc???????", false, "abc???????"));
    EXPECT_THAT(the_parser<Apm1> | SUCCEEDS_PARSING("abc ??abc???????", true, " ??abc???????"));
    EXPECT_THAT(the_parser<Apm1> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING("abcabcabcabc??", 36, ""));
    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING("abcabcabcabc", 12, ""));
    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING("abcabcabcabc ??", 12, " ??"));
    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING("abc", 3, ""));
    EXPECT_THAT(the_parser<Apm2> | FAILS_PARSING(" abc"));
    EXPECT_THAT(the_parser<Apm2> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Apm1> | SUCCEEDS_PARSING(L"abc???????", false, L"?"));
    EXPECT_THAT(the_parser<Apm1> | FAILS_PARSING(L"??abc???????"));
    EXPECT_THAT(the_parser<Apm1> | SUCCEEDS_PARSING(L"abc??abc???????", false, L"abc???????"));
    EXPECT_THAT(the_parser<Apm1> | SUCCEEDS_PARSING(L"abc ??abc???????", true, L" ??abc???????"));
    EXPECT_THAT(the_parser<Apm1> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING(L"abcabcabcabc??", 36, L""));
    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING(L"abcabcabcabc", 12, L""));
    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING(L"abcabcabcabc ??", 12, L" ??"));
    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING(L"abc", 3, L""));
    EXPECT_THAT(the_parser<Apm2> | FAILS_PARSING(L" abc"));
    EXPECT_THAT(the_parser<Apm2> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Apm1> | SUCCEEDS_PARSING(e<int>("abc???????"), false, e<int>("?")));
    EXPECT_THAT(the_parser<Apm1> | FAILS_PARSING(e<int>("??abc???????")));
    EXPECT_THAT(the_parser<Apm1> | SUCCEEDS_PARSING(e<int>("abc??abc???????"), false, e<int>("abc???????")));
    EXPECT_THAT(the_parser<Apm1> | SUCCEEDS_PARSING(e<int>("abc ??abc???????"), true, e<int>(" ??abc???????")));
    EXPECT_THAT(the_parser<Apm1> | FAILS_PARSING(e<int>("")));

    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING(e<int>("abcabcabcabc??"), 36, e<int>("")));
    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING(e<int>("abcabcabcabc"), 12, e<int>("")));
    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING(e<int>("abcabcabcabc ??"), 12, e<int>(" ??")));
    EXPECT_THAT(the_parser<Apm2> | SUCCEEDS_PARSING(e<int>("abc"), 3, e<int>("")));
    EXPECT_THAT(the_parser<Apm2> | FAILS_PARSING(e<int>(" abc")));
    EXPECT_THAT(the_parser<Apm2> | FAILS_PARSING(e<int>("")));
}

TEST("apply_map_parser", "Move only")
{
    {
        using tuple = std::tuple<output_span<char>, output_span<char>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_map_parser<sequence_parser<Any3, ABC>, integral_constant<T::make>>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("xabcd", T(std::tuple("x", "abc")), "d"));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING("ydcba"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("zabcabcd", T(std::tuple("z", "abc")), "abcd"));
    }

    {
        using tuple = std::tuple<output_span<wchar_t>, output_span<wchar_t>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_map_parser<sequence_parser<Any3, ABC>, integral_constant<T::make>>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"xabcd", T(std::tuple(L"x", L"abc")), L"d"));
        EXPECT_THAT(the_parser<P> | FAILS_PARSING(L"ydcba"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"zabcabcd", T(std::tuple(L"z", L"abc")), L"abcd"));
    }

    {
        using tuple = std::tuple<output_span<int>, output_span<int>>;
        using T = MoveOnlyWrapper<tuple>;
        using P = apply_map_parser<sequence_parser<Any3, ABC>, integral_constant<T::make>>;
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
