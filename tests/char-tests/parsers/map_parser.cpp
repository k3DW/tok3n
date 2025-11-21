// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("map_parser");

TEST("map_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Map1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Map2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Map3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Map4> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Map1> | has_family<map_family>);
    EXPECT_THAT(the_parser<Map2> | has_family<map_family>);
    EXPECT_THAT(the_parser<Map3> | has_family<map_family>);
    EXPECT_THAT(the_parser<Map4> | has_family<map_family>);

#if defined(VALUE_TYPE_CHAR)
    EXPECT_THAT(the_parser<Map1> | is_parser_for<char>.with_result<std::size_t>);
#elif defined(VALUE_TYPE_WCHAR_T)
    EXPECT_THAT(the_parser<Map1> | is_not_parser_for<char>);
#else
#error
#endif
    EXPECT_THAT(the_parser<Map2> | is_parser_for<char>.with_result<std::vector<char>>);
    EXPECT_THAT(the_parser<Map3> | is_parser_for<char>.with_result<bool>);
    EXPECT_THAT(the_parser<Map4> | is_parser_for<char>.with_result<std::size_t>);

#if defined(VALUE_TYPE_CHAR)
    EXPECT_THAT(the_parser<Map1> | is_not_parser_for<wchar_t>);
#elif defined(VALUE_TYPE_WCHAR_T)
    EXPECT_THAT(the_parser<Map1> | is_parser_for<wchar_t>.with_result<std::size_t>);
#else
#error
#endif
    EXPECT_THAT(the_parser<Map2> | is_parser_for<wchar_t>.with_result<std::vector<wchar_t>>);
    EXPECT_THAT(the_parser<Map3> | is_parser_for<wchar_t>.with_result<bool>);
    EXPECT_THAT(the_parser<Map4> | is_parser_for<wchar_t>.with_result<std::size_t>);

    EXPECT_THAT(the_parser<Map1> | is_not_parser_for<int>);
    EXPECT_THAT(the_parser<Map2> | is_parser_for<int>.with_result<std::vector<int>>);
    EXPECT_THAT(the_parser<Map3> | is_parser_for<int>.with_result<bool>);
    EXPECT_THAT(the_parser<Map4> | is_parser_for<int>.with_result<std::size_t>);
}

TEST("map_parser", "Parse all")
{
    EXPECT_THAT(the_parser<Map1> | SUCCEEDS_PARSING(TT("abcabcabcab"), 3, TT("ab")));
    ASSERT_PARSE_FAILURE(Map1, TT(""));
    ASSERT_PARSE_FAILURE(Map1, TT("ab"));
    EXPECT_THAT(the_parser<Map1> | SUCCEEDS_PARSING(TT("abc"), 1, TT("")));

    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING("abcabc", std::vector<char>({ 'a', 'b', 'c' }), "abc"));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING("a??bcabc", std::vector<char>{}, "a??bcabc"));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING("", std::vector<char>{}, ""));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING("??abcabc", std::vector<char>({ '?', '?' }), "abcabc"));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(" ??abcabc", std::vector<char>{}, " ??abcabc"));

    EXPECT_THAT(the_parser<Map3> | SUCCEEDS_PARSING("abc???????", false, "?"));
    ASSERT_PARSE_FAILURE(Map3, "??abc???????");
    EXPECT_THAT(the_parser<Map3> | SUCCEEDS_PARSING("abc??abc???????", false, "abc???????"));
    EXPECT_THAT(the_parser<Map3> | SUCCEEDS_PARSING("abc ??abc???????", true, " ??abc???????"));
    ASSERT_PARSE_FAILURE(Map3, "");

    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING("abcabcabcabc??", 36, ""));
    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING("abcabcabcabc", 12, ""));
    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING("abcabcabcabc ??", 12, " ??"));
    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING("abc", 3, ""));
    ASSERT_PARSE_FAILURE(Map4, " abc");
    ASSERT_PARSE_FAILURE(Map4, "");

    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(L"abcabc", std::vector<wchar_t>({ 'a', 'b', 'c' }), L"abc"));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(L"a??bcabc", std::vector<wchar_t>{}, L"a??bcabc"));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(L"", std::vector<wchar_t>{}, L""));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(L"??abcabc", std::vector<wchar_t>({ '?', '?' }), L"abcabc"));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(L" ??abcabc", std::vector<wchar_t>{}, L" ??abcabc"));

    EXPECT_THAT(the_parser<Map3> | SUCCEEDS_PARSING(L"abc???????", false, L"?"));
    ASSERT_PARSE_FAILURE(Map3, L"??abc???????");
    EXPECT_THAT(the_parser<Map3> | SUCCEEDS_PARSING(L"abc??abc???????", false, L"abc???????"));
    EXPECT_THAT(the_parser<Map3> | SUCCEEDS_PARSING(L"abc ??abc???????", true, L" ??abc???????"));
    ASSERT_PARSE_FAILURE(Map3, L"");

    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING(L"abcabcabcabc??", 36, L""));
    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING(L"abcabcabcabc", 12, L""));
    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING(L"abcabcabcabc ??", 12, L" ??"));
    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING(L"abc", 3, L""));
    ASSERT_PARSE_FAILURE(Map4, L" abc");
    ASSERT_PARSE_FAILURE(Map4, L"");

    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(e<int>("abcabc"), std::vector<int>({ 'a', 'b', 'c' }), e<int>("abc")));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(e<int>("a??bcabc"), std::vector<int>{}, e<int>("a??bcabc")));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(e<int>(""), std::vector<int>{}, e<int>("")));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(e<int>("??abcabc"), std::vector<int>({ '?', '?' }), e<int>("abcabc")));
    EXPECT_THAT(the_parser<Map2> | SUCCEEDS_PARSING(e<int>(" ??abcabc"), std::vector<int>{}, e<int>(" ??abcabc")));

    EXPECT_THAT(the_parser<Map3> | SUCCEEDS_PARSING(e<int>("abc???????"), false, e<int>("?")));
    ASSERT_PARSE_FAILURE(Map3, e<int>("??abc???????"));
    EXPECT_THAT(the_parser<Map3> | SUCCEEDS_PARSING(e<int>("abc??abc???????"), false, e<int>("abc???????")));
    EXPECT_THAT(the_parser<Map3> | SUCCEEDS_PARSING(e<int>("abc ??abc???????"), true, e<int>(" ??abc???????")));
    ASSERT_PARSE_FAILURE(Map3, e<int>(""));

    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING(e<int>("abcabcabcabc??"), 36, e<int>("")));
    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING(e<int>("abcabcabcabc"), 12, e<int>("")));
    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING(e<int>("abcabcabcabc ??"), 12, e<int>(" ??")));
    EXPECT_THAT(the_parser<Map4> | SUCCEEDS_PARSING(e<int>("abc"), 3, e<int>("")));
    ASSERT_PARSE_FAILURE(Map4, e<int>(" abc"));
    ASSERT_PARSE_FAILURE(Map4, e<int>(""));
}

TEST("map_parser", "Move only")
{
    {
        using T = MoveOnlyWrapper<output_span<char>>;
        using P = map_parser<ABC, integral_constant<T::make>>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcd", T("abc"), "d"));
        ASSERT_PARSE_FAILURE(P, "dcba");
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcabcd", T("abc"), "abcd"));
    }

    {
        using T = MoveOnlyWrapper<output_span<wchar_t>>;
        using P = map_parser<ABC, integral_constant<T::make>>;
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcd", T(L"abc"), L"d"));
        ASSERT_PARSE_FAILURE(P, L"dcba");
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcabcd", T(L"abc"), L"abcd"));
    }

    {
        using T = MoveOnlyWrapper<output_span<int>>;
        using P = map_parser<ABC, integral_constant<T::make>>;
        static constexpr auto arr_abc = e<int>("abc");
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcd"), T(arr_abc), e<int>("d")));
        ASSERT_PARSE_FAILURE(P, e<int>("dcba"));
        EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcabcd"), T(arr_abc), e<int>("abcd")));
    }
}

TEST("map_parser", "void input")
{
    using P = ignore_parser<ABC>;

    constexpr auto func_good = []() { return 0; };
    using MapGood = map_parser<P, integral_constant<func_good>>;
    EXPECT_THAT(the_parser<MapGood> | has_family<map_family>);
    EXPECT_THAT(the_parser<MapGood> | is_parser_for<value_type>.with_result<int>);
    EXPECT_THAT(the_parser<MapGood> | SUCCEEDS_PARSING("abcd", 0, "d"));
    ASSERT_PARSE_FAILURE(MapGood, " abcd");

    constexpr auto func_bad = [](auto) { return 0; };
    using MapBad = map_parser<P, integral_constant<func_bad>>;
    EXPECT_THAT(the_parser<MapBad> | has_family<map_family>);
    EXPECT_THAT(the_parser<MapBad> | is_not_parser_for<value_type>);
}

TEST("map_parser", "void output")
{
    using P = ABC;

    constexpr auto func_good = [](auto) {};
    using MapGood = map_parser<P, integral_constant<func_good>>;
    EXPECT_THAT(the_parser<MapGood> | is_parser_for<value_type>.with_result<void>);
    ASSERT_PARSE_SUCCESS_VOID(MapGood, "abcd", "d");
    ASSERT_PARSE_FAILURE(MapGood, " abcd");

    constexpr auto func_bad = []() {};
    using MapBad = map_parser<P, integral_constant<func_bad>>;
    EXPECT_THAT(the_parser<MapBad> | has_family<map_family>);
    EXPECT_THAT(the_parser<MapBad> | is_not_parser_for<value_type>);
}

TEST("map_parser", "void input and void output")
{
    using P = ignore_parser<ABC>;

    constexpr auto func_good = []() {};
    using MapGood = map_parser<P, integral_constant<func_good>>;
    EXPECT_THAT(the_parser<MapGood> | is_parser_for<value_type>.with_result<void>);
    ASSERT_PARSE_SUCCESS_VOID(MapGood, "abcd", "d");
    ASSERT_PARSE_FAILURE(MapGood, " abcd");

    constexpr auto func_bad = [](auto) {};
    using MapBad = map_parser<P, integral_constant<func_bad>>;
    EXPECT_THAT(the_parser<MapBad> | has_family<map_family>);
    EXPECT_THAT(the_parser<MapBad> | is_not_parser_for<value_type>);
}

} // namespace
} // namespace k3::tok3n::tests
