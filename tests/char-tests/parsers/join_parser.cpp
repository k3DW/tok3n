// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("join_parser");

TEST("join_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Joi1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Joi2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Joi3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Joi4> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Joi5> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Joi1> | has_family<join_family>);
    EXPECT_THAT(the_parser<Joi2> | has_family<join_family>);
    EXPECT_THAT(the_parser<Joi3> | has_family<join_family>);
    EXPECT_THAT(the_parser<Joi4> | has_family<join_family>);
    EXPECT_THAT(the_parser<Joi5> | has_family<join_family>);

    EXPECT_THAT(the_parser<Joi1> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Joi2> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Joi3> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Joi4> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Joi5> | is_parser_for<char>.with_result<output_span<char>>);

    EXPECT_THAT(the_parser<Joi1> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Joi2> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Joi3> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Joi4> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Joi5> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);

    EXPECT_THAT(the_parser<Joi1> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Joi2> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Joi3> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Joi4> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Joi5> | is_parser_for<int>.with_result<output_span<int>>);
}

TEST("join_parser", "Parse all")
{
    EXPECT_THAT(the_parser<Joi1> | SUCCEEDS_PARSING("abcabc", "abc", "abc"));
    EXPECT_THAT(the_parser<Joi1> | FAILS_PARSING("Abcabc"));
    EXPECT_THAT(the_parser<Joi1> | FAILS_PARSING(" abcabc"));

    EXPECT_THAT(the_parser<Joi2> | SUCCEEDS_PARSING("abcabcabcab", "abcabcabc", "ab"));
    EXPECT_THAT(the_parser<Joi2> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Joi2> | FAILS_PARSING("ab"));
    EXPECT_THAT(the_parser<Joi2> | SUCCEEDS_PARSING("abc", "abc", ""));

    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING("abcabc", "abc", "abc"));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING("a??bcabc", "", "a??bcabc"));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING("", "", ""));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING("??abcabc", "??", "abcabc"));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(" ??abcabc", "", " ??abcabc"));

    EXPECT_THAT(the_parser<Joi4> | SUCCEEDS_PARSING("abc???????", "abc??????", "?"));
    EXPECT_THAT(the_parser<Joi4> | FAILS_PARSING("??abc???????"));
    EXPECT_THAT(the_parser<Joi4> | SUCCEEDS_PARSING("abc??abc???????", "abc??", "abc???????"));
    EXPECT_THAT(the_parser<Joi4> | SUCCEEDS_PARSING("abc ??abc???????", "abc", " ??abc???????"));
    EXPECT_THAT(the_parser<Joi4> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING("abcabcabcabc??", "abcabcabcabc??", ""));
    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING("abcabcabcabc", "abcabcabcabc", ""));
    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING("abcabcabcabc ??", "abcabcabcabc", " ??"));
    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING("abc", "abc", ""));
    EXPECT_THAT(the_parser<Joi5> | FAILS_PARSING(" abc"));
    EXPECT_THAT(the_parser<Joi5> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Joi1> | SUCCEEDS_PARSING(L"abcabc", L"abc", L"abc"));
    EXPECT_THAT(the_parser<Joi1> | FAILS_PARSING(L"Abcabc"));
    EXPECT_THAT(the_parser<Joi1> | FAILS_PARSING(L" abcabc"));

    EXPECT_THAT(the_parser<Joi2> | SUCCEEDS_PARSING(L"abcabcabcab", L"abcabcabc", L"ab"));
    EXPECT_THAT(the_parser<Joi2> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Joi2> | FAILS_PARSING(L"ab"));
    EXPECT_THAT(the_parser<Joi2> | SUCCEEDS_PARSING(L"abc", L"abc", L""));

    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(L"abcabc", L"abc", L"abc"));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(L"a??bcabc", L"", L"a??bcabc"));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(L"", L"", L""));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(L"??abcabc", L"??", L"abcabc"));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(L" ??abcabc", L"", L" ??abcabc"));

    EXPECT_THAT(the_parser<Joi4> | SUCCEEDS_PARSING(L"abc???????", L"abc??????", L"?"));
    EXPECT_THAT(the_parser<Joi4> | FAILS_PARSING(L"??abc???????"));
    EXPECT_THAT(the_parser<Joi4> | SUCCEEDS_PARSING(L"abc??abc???????", L"abc??", L"abc???????"));
    EXPECT_THAT(the_parser<Joi4> | SUCCEEDS_PARSING(L"abc ??abc???????", L"abc", L" ??abc???????"));
    EXPECT_THAT(the_parser<Joi4> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING(L"abcabcabcabc??", L"abcabcabcabc??", L""));
    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING(L"abcabcabcabc", L"abcabcabcabc", L""));
    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING(L"abcabcabcabc ??", L"abcabcabcabc", L" ??"));
    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING(L"abc", L"abc", L""));
    EXPECT_THAT(the_parser<Joi5> | FAILS_PARSING(L" abc"));
    EXPECT_THAT(the_parser<Joi5> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Joi1> | SUCCEEDS_PARSING(e<int>("abcabc"), e<int>("abc"), e<int>("abc")));
    EXPECT_THAT(the_parser<Joi1> | FAILS_PARSING(e<int>("Abcabc")));
    EXPECT_THAT(the_parser<Joi1> | FAILS_PARSING(e<int>(" abcabc")));

    EXPECT_THAT(the_parser<Joi2> | SUCCEEDS_PARSING(e<int>("abcabcabcab"), e<int>("abcabcabc"), e<int>("ab")));
    EXPECT_THAT(the_parser<Joi2> | FAILS_PARSING(e<int>("")));
    EXPECT_THAT(the_parser<Joi2> | FAILS_PARSING(e<int>("ab")));
    EXPECT_THAT(the_parser<Joi2> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("abc"), e<int>("")));

    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(e<int>("abcabc"), e<int>("abc"), e<int>("abc")));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(e<int>("a??bcabc"), e<int>(""), e<int>("a??bcabc")));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(e<int>(""), e<int>(""), e<int>("")));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(e<int>("??abcabc"), e<int>("??"), e<int>("abcabc")));
    EXPECT_THAT(the_parser<Joi3> | SUCCEEDS_PARSING(e<int>(" ??abcabc"), e<int>(""), e<int>(" ??abcabc")));

    EXPECT_THAT(the_parser<Joi4> | SUCCEEDS_PARSING(e<int>("abc???????"), e<int>("abc??????"), e<int>("?")));
    EXPECT_THAT(the_parser<Joi4> | FAILS_PARSING(e<int>("??abc???????")));
    EXPECT_THAT(the_parser<Joi4> | SUCCEEDS_PARSING(e<int>("abc??abc???????"), e<int>("abc??"), e<int>("abc???????")));
    EXPECT_THAT(the_parser<Joi4> | SUCCEEDS_PARSING(e<int>("abc ??abc???????"), e<int>("abc"), e<int>(" ??abc???????")));
    EXPECT_THAT(the_parser<Joi4> | FAILS_PARSING(e<int>("")));

    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING(e<int>("abcabcabcabc??"), e<int>("abcabcabcabc??"), e<int>("")));
    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING(e<int>("abcabcabcabc"), e<int>("abcabcabcabc"), e<int>("")));
    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING(e<int>("abcabcabcabc ??"), e<int>("abcabcabcabc"), e<int>(" ??")));
    EXPECT_THAT(the_parser<Joi5> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("abc"), e<int>("")));
    EXPECT_THAT(the_parser<Joi5> | FAILS_PARSING(e<int>(" abc")));
    EXPECT_THAT(the_parser<Joi5> | FAILS_PARSING(e<int>("")));
}

TEST("join_parser", "Contiguous empty strings")
{
    using J1 = join_parser<maybe_parser<choice_parser<ABC, QQ>>>;
    using J2 = join_parser<zero_or_more_parser<sequence_parser<All1, Any2>>>;

    using P = join_parser<sequence_parser<all_of_parser<TT("**start**")>, J1, J2, all_of_parser<TT("__end__")>>>;

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("**start**__end__", "**start**__end__", ""));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"**start**__end__", L"**start**__end__", L""));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("**start**__end__"), e<int>("**start**__end__"), e<int>("")));
}



TEST("join_parser", "join_parser<delimit_parser>")
{
    using D = delimit_parser<ABC, ignore_parser<QQ>>;
    using J = join_parser<D>;

    {
        using vec_type = std::vector<output_span<char>>;
        EXPECT_THAT(the_parser<D> | SUCCEEDS_PARSING("abc", vec_type({ "abc" }), ""));
        EXPECT_THAT(the_parser<D> | SUCCEEDS_PARSING("abc??abc??a", vec_type({ "abc", "abc" }), "??a"));
        EXPECT_THAT(the_parser<D> | SUCCEEDS_PARSING("abc??abc??abc", vec_type({ "abc", "abc", "abc" }), ""));
        EXPECT_THAT(the_parser<J> | SUCCEEDS_PARSING("abc", "abc", ""));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J, "abc??abc??a", "??a");
        ASSERT_PARSE_LOOKAHEAD_ONLY(J, "abc??abc??abc", "");
    }

    {
        using vec_type = std::vector<output_span<wchar_t>>;
        EXPECT_THAT(the_parser<D> | SUCCEEDS_PARSING(L"abc", vec_type({ L"abc" }), L""));
        EXPECT_THAT(the_parser<D> | SUCCEEDS_PARSING(L"abc??abc??a", vec_type({ L"abc", L"abc" }), L"??a"));
        EXPECT_THAT(the_parser<D> | SUCCEEDS_PARSING(L"abc??abc??abc", vec_type({ L"abc", L"abc", L"abc" }), L""));
        EXPECT_THAT(the_parser<J> | SUCCEEDS_PARSING(L"abc", L"abc", L""));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J, L"abc??abc??a", L"??a");
        ASSERT_PARSE_LOOKAHEAD_ONLY(J, L"abc??abc??abc", L"");
    }

    static constexpr auto arr_abc = e<int>("abc");

    {
        using vec_type = std::vector<output_span<int>>;
        EXPECT_THAT(the_parser<D> | SUCCEEDS_PARSING(e<int>("abc"), vec_type({ arr_abc }), e<int>("")));
        EXPECT_THAT(the_parser<D> | SUCCEEDS_PARSING(e<int>("abc??abc??a"), vec_type({ arr_abc, arr_abc }), e<int>("??a")));
        EXPECT_THAT(the_parser<D> | SUCCEEDS_PARSING(e<int>("abc??abc??abc"), vec_type({ arr_abc, arr_abc, arr_abc }), e<int>("")));
        EXPECT_THAT(the_parser<J> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("abc"), e<int>("")));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J, e<int>("abc??abc??a"), e<int>("??a"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J, e<int>("abc??abc??abc"), e<int>(""));
    }
}

TEST("join_parser", "join_parser<ignore_parser>")
{
    using Q = any_of_parser<TT("?")>;

    using S1 = sequence_parser<ABC, ignore_parser<QQ>>;
    using S2 = sequence_parser<ABC, ignore_parser<QQ>, ABC>;
    using S3 = sequence_parser<ABC, QQ, ABC>;
    using S4 = sequence_parser<ABC, Q, Q, ABC>;
    using J1 = join_parser<S1>;
    using J2 = join_parser<S2>;
    using J3 = join_parser<S3>;
    using J4 = join_parser<S4>;

    EXPECT_THAT(the_parser<S1> | SUCCEEDS_PARSING("abc??abc", "abc", "abc"));
    EXPECT_THAT(the_parser<S1> | SUCCEEDS_PARSING("abc??abc??a", "abc", "abc??a"));
    EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING("abc??abc", "abc", "abc"));
    EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING("abc??abc??a", "abc", "abc??a"));

    EXPECT_THAT(the_parser<S2> | SUCCEEDS_PARSING("abc??abc", std::tuple("abc", "abc"), ""));
    EXPECT_THAT(the_parser<S2> | SUCCEEDS_PARSING("abc??abc??a", std::tuple("abc", "abc"), "??a"));
    ASSERT_PARSE_LOOKAHEAD_ONLY(J2, "abc??abc", "");
    ASSERT_PARSE_LOOKAHEAD_ONLY(J2, "abc??abc??a", "??a");

    EXPECT_THAT(the_parser<S3> | SUCCEEDS_PARSING("abc??abc", std::tuple("abc", "??", "abc"), ""));
    EXPECT_THAT(the_parser<S3> | SUCCEEDS_PARSING("abc??abc??a", std::tuple("abc", "??", "abc"), "??a"));
    EXPECT_THAT(the_parser<J3> | SUCCEEDS_PARSING("abc??abc", "abc??abc", ""));
    EXPECT_THAT(the_parser<J3> | SUCCEEDS_PARSING("abc??abc??a", "abc??abc", "??a"));

    EXPECT_THAT(the_parser<S4> | SUCCEEDS_PARSING("abc??abc", std::tuple("abc", "?", "?", "abc"), ""));
    EXPECT_THAT(the_parser<S4> | SUCCEEDS_PARSING("abc??abc??a", std::tuple("abc", "?", "?", "abc"), "??a"));
    EXPECT_THAT(the_parser<J4> | SUCCEEDS_PARSING("abc??abc", "abc??abc", ""));
    EXPECT_THAT(the_parser<J4> | SUCCEEDS_PARSING("abc??abc??a", "abc??abc", "??a"));

    EXPECT_THAT(the_parser<S1> | SUCCEEDS_PARSING(L"abc??abc", L"abc", L"abc"));
    EXPECT_THAT(the_parser<S1> | SUCCEEDS_PARSING(L"abc??abc??a", L"abc", L"abc??a"));
    EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING(L"abc??abc", L"abc", L"abc"));
    EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING(L"abc??abc??a", L"abc", L"abc??a"));

    EXPECT_THAT(the_parser<S2> | SUCCEEDS_PARSING(L"abc??abc", std::tuple(L"abc", L"abc"), L""));
    EXPECT_THAT(the_parser<S2> | SUCCEEDS_PARSING(L"abc??abc??a", std::tuple(L"abc", L"abc"), L"??a"));
    ASSERT_PARSE_LOOKAHEAD_ONLY(J2, L"abc??abc", L"");
    ASSERT_PARSE_LOOKAHEAD_ONLY(J2, L"abc??abc??a", L"??a");

    EXPECT_THAT(the_parser<S3> | SUCCEEDS_PARSING(L"abc??abc", std::tuple(L"abc", L"??", L"abc"), L""));
    EXPECT_THAT(the_parser<S3> | SUCCEEDS_PARSING(L"abc??abc??a", std::tuple(L"abc", L"??", L"abc"), L"??a"));
    EXPECT_THAT(the_parser<J3> | SUCCEEDS_PARSING(L"abc??abc", L"abc??abc", L""));
    EXPECT_THAT(the_parser<J3> | SUCCEEDS_PARSING(L"abc??abc??a", L"abc??abc", L"??a"));

    EXPECT_THAT(the_parser<S4> | SUCCEEDS_PARSING(L"abc??abc", std::tuple(L"abc", L"?", L"?", L"abc"), L""));
    EXPECT_THAT(the_parser<S4> | SUCCEEDS_PARSING(L"abc??abc??a", std::tuple(L"abc", L"?", L"?", L"abc"), L"??a"));
    EXPECT_THAT(the_parser<J4> | SUCCEEDS_PARSING(L"abc??abc", L"abc??abc", L""));
    EXPECT_THAT(the_parser<J4> | SUCCEEDS_PARSING(L"abc??abc??a", L"abc??abc", L"??a"));

    EXPECT_THAT(the_parser<S1> | SUCCEEDS_PARSING(e<int>("abc??abc"), e<int>("abc"), e<int>("abc")));
    EXPECT_THAT(the_parser<S1> | SUCCEEDS_PARSING(e<int>("abc??abc??a"), e<int>("abc"), e<int>("abc??a")));
    EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING(e<int>("abc??abc"), e<int>("abc"), e<int>("abc")));
    EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING(e<int>("abc??abc??a"), e<int>("abc"), e<int>("abc??a")));

    EXPECT_THAT(the_parser<S2> | SUCCEEDS_PARSING(e<int>("abc??abc"), std::tuple(e<int>("abc"), e<int>("abc")), e<int>("")));
    EXPECT_THAT(the_parser<S2> | SUCCEEDS_PARSING(e<int>("abc??abc??a"), std::tuple(e<int>("abc"), e<int>("abc")), e<int>("??a")));
    ASSERT_PARSE_LOOKAHEAD_ONLY(J2, e<int>("abc??abc"), e<int>(""));
    ASSERT_PARSE_LOOKAHEAD_ONLY(J2, e<int>("abc??abc??a"), e<int>("??a"));

    EXPECT_THAT(the_parser<S3> | SUCCEEDS_PARSING(e<int>("abc??abc"), std::tuple(e<int>("abc"), e<int>("??"), e<int>("abc")), e<int>("")));
    EXPECT_THAT(the_parser<S3> | SUCCEEDS_PARSING(e<int>("abc??abc??a"), std::tuple(e<int>("abc"), e<int>("??"), e<int>("abc")), e<int>("??a")));
    EXPECT_THAT(the_parser<J3> | SUCCEEDS_PARSING(e<int>("abc??abc"), e<int>("abc??abc"), e<int>("")));
    EXPECT_THAT(the_parser<J3> | SUCCEEDS_PARSING(e<int>("abc??abc??a"), e<int>("abc??abc"), e<int>("??a")));

    EXPECT_THAT(the_parser<S4> | SUCCEEDS_PARSING(e<int>("abc??abc"), std::tuple(e<int>("abc"), e<int>("?"), e<int>("?"), e<int>("abc")), e<int>("")));
    EXPECT_THAT(the_parser<S4> | SUCCEEDS_PARSING(e<int>("abc??abc??a"), std::tuple(e<int>("abc"), e<int>("?"), e<int>("?"), e<int>("abc")), e<int>("??a")));
    EXPECT_THAT(the_parser<J4> | SUCCEEDS_PARSING(e<int>("abc??abc"), e<int>("abc??abc"), e<int>("")));
    EXPECT_THAT(the_parser<J4> | SUCCEEDS_PARSING(e<int>("abc??abc??a"), e<int>("abc??abc"), e<int>("??a")));
}

TEST("join_parser", "join_parser<map_parser>")
{
    constexpr auto f = [](auto&& v)
    {
        using V = std::ranges::range_value_t<decltype(v)>;
        if constexpr (std::same_as<V, char> or std::same_as<V, output_span<char>>)
            return output_span<char>((v.size() % 2 == 0) ? "a" : "b");
        else if constexpr (std::same_as<V, wchar_t> or std::same_as<V, output_span<wchar_t>>)
            return output_span<wchar_t>((v.size() % 2 == 0) ? L"a" : L"b");
        else if constexpr (std::same_as<V, int> or std::same_as<V, output_span<int>>)
        {
            constexpr auto a = e<int>("a");
            constexpr auto b = e<int>("b");
            return output_span<int>((v.size() % 2 == 0) ? a : b);
        }
        else
            static_assert(std::same_as<V, void>);
    };

    using T1 = map_parser<ABC, integral_constant<f>>;
    using T2 = sequence_parser<map_parser<ABC, integral_constant<f>>, QQ>;
    using T3 = zero_or_more_parser<sequence_parser<map_parser<one_or_more_parser<ABC>, integral_constant<f>>, QQ>>;
    using J1 = join_parser<T1>;
    using J2 = join_parser<T2>;
    using J3 = join_parser<T3>;

    {
        EXPECT_THAT(the_parser<T1> | SUCCEEDS_PARSING("abcabc", "b", "abc"));
        EXPECT_THAT(the_parser<T1> | SUCCEEDS_PARSING("abc", "b", ""));
        EXPECT_THAT(the_parser<T1> | FAILS_PARSING(""));
        EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING("abcabc", "b", "abc"));
        EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING("abc", "b", ""));
        EXPECT_THAT(the_parser<J1> | FAILS_PARSING(""));

        EXPECT_THAT(the_parser<T2> | SUCCEEDS_PARSING("abc??abc", std::tuple("b", "??"), "abc"));
        EXPECT_THAT(the_parser<T2> | SUCCEEDS_PARSING("abc??", std::tuple("b", "??"), ""));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J2, "abc??abc", "abc");
        ASSERT_PARSE_LOOKAHEAD_ONLY(J2, "abc??", "");

        using vec_type = std::vector<std::tuple<output_span<char>, output_span<char>>>;
        EXPECT_THAT(the_parser<T3> | SUCCEEDS_PARSING("abcabc??abc??ab", vec_type({ { "a", "??" }, { "b", "??" } }), "ab"));
        EXPECT_THAT(the_parser<T3> | SUCCEEDS_PARSING("abc??abcabcabcabc??", vec_type({ { "b", "??" }, { "a", "??" } }), ""));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J3, "abcabc??abc??ab", "ab");
        ASSERT_PARSE_LOOKAHEAD_ONLY(J3, "abc??abcabcabcabc??", "");
    }

    {
        EXPECT_THAT(the_parser<T1> | SUCCEEDS_PARSING(L"abcabc", L"b", L"abc"));
        EXPECT_THAT(the_parser<T1> | SUCCEEDS_PARSING(L"abc", L"b", L""));
        EXPECT_THAT(the_parser<T1> | FAILS_PARSING(L""));
        EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING(L"abcabc", L"b", L"abc"));
        EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING(L"abc", L"b", L""));
        EXPECT_THAT(the_parser<J1> | FAILS_PARSING(L""));

        EXPECT_THAT(the_parser<T2> | SUCCEEDS_PARSING(L"abc??abc", std::tuple(L"b", L"??"), L"abc"));
        EXPECT_THAT(the_parser<T2> | SUCCEEDS_PARSING(L"abc??", std::tuple(L"b", L"??"), L""));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J2, L"abc??abc", L"abc");
        ASSERT_PARSE_LOOKAHEAD_ONLY(J2, L"abc??", L"");

        using vec_type = std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>;
        EXPECT_THAT(the_parser<T3> | SUCCEEDS_PARSING(L"abcabc??abc??ab", vec_type({ { L"a", L"??" }, { L"b", L"??" } }), L"ab"));
        EXPECT_THAT(the_parser<T3> | SUCCEEDS_PARSING(L"abc??abcabcabcabc??", vec_type({ { L"b", L"??" }, { L"a", L"??" } }), L""));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J3, L"abcabc??abc??ab", L"ab");
        ASSERT_PARSE_LOOKAHEAD_ONLY(J3, L"abc??abcabcabcabc??", L"");
    }

    {
        // TODO: The commented out lines have different compile-time and run-time results
        //EXPECT_THAT(the_parser<T1> | SUCCEEDS_PARSING(e<int>("abcabc"), e<int>("b"), e<int>("abc")));
        //EXPECT_THAT(the_parser<T1> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("b"), e<int>("")));
        EXPECT_THAT(the_parser<T1> | FAILS_PARSING(e<int>("")));
        //EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING(e<int>("abcabc"), e<int>("b"), e<int>("abc")));
        //EXPECT_THAT(the_parser<J1> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("b"), e<int>("")));
        EXPECT_THAT(the_parser<J1> | FAILS_PARSING(e<int>("")));

        //EXPECT_THAT(the_parser<T2> | SUCCEEDS_PARSING(e<int>("abc??abc"), std::tuple(e<int>("b"), e<int>("??")), e<int>("abc")));
        //EXPECT_THAT(the_parser<T2> | SUCCEEDS_PARSING(e<int>("abc??"), std::tuple(e<int>("b"), e<int>("??")), e<int>("")));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J2, e<int>("abc??abc"), e<int>("abc"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J2, e<int>("abc??"), e<int>(""));

        // static constexpr auto arr_qq = e<int>("??");
        // static constexpr auto arr_a = e<int>("a");
        // static constexpr auto arr_b = e<int>("b");

        using vec_type [[maybe_unused]] = std::vector<std::tuple<output_span<int>, output_span<int>>>;
        //EXPECT_THAT(the_parser<T3> | SUCCEEDS_PARSING(e<int>("abcabc??abc??ab"), vec_type({ { arr_a, arr_qq }, { arr_b, arr_qq } }), e<int>("ab")));
        //EXPECT_THAT(the_parser<T3> | SUCCEEDS_PARSING(e<int>("abc??abcabcabcabc??"), vec_type({ { arr_b, arr_qq }, { arr_a, arr_qq } }), e<int>("")));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J3, e<int>("abcabc??abc??ab"), e<int>("ab"));
        ASSERT_PARSE_LOOKAHEAD_ONLY(J3, e<int>("abc??abcabcabcabc??"), e<int>(""));
    }
}

TEST("join_parser", "join_parser<sequence_parser<choice_parser<non-eps,eps>, anything>>")
{
    auto seq = (TT("+-"_any) | eps) >> TT("abc"_all);
    using Seq = decltype(seq);
    EXPECT_THAT(the_parser<Seq> | has_family<sequence_family>);
    EXPECT_THAT(the_parser<Seq> | (is_parser_for<char>.with_result<std::tuple<output_span<char>,output_span<char>>>));
    EXPECT_THAT(the_parser<Seq> | (is_parser_for<wchar_t>.with_result<std::tuple<output_span<wchar_t>,output_span<wchar_t>>>));
    EXPECT_THAT(the_parser<Seq> | (is_parser_for<int>.with_result<std::tuple<output_span<int>,output_span<int>>>));

    using P = join_parser<Seq>;

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("+abcd", "+abc", "d"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("-abcd", "-abc", "d"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcd", "abc", "d"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(" abcd"));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"+abcd", L"+abc", L"d"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"-abcd", L"-abc", L"d"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcd", L"abc", L"d"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L" abcd"));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("+abcd"), e<int>("+abc"), e<int>("d")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("-abcd"), e<int>("-abc"), e<int>("d")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcd"), e<int>("abc"), e<int>("d")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>(" abcd")));
}

TEST("join_parser", "join variant")
{
    constexpr auto passthrough = [](auto val) { return val; };
    using LHS = map_parser<ABC, integral_constant<passthrough>>;
    using RHS = sequence_parser<Comma, QQ>;
    using Inner = choice_parser<LHS, RHS>;
    static_assert(not guaranteed_contiguous<Inner>); // Avoid the optimization
    using P = join_parser<Inner>;

    EXPECT_THAT(the_parser<Inner> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Inner> | has_family<choice_family>);
    EXPECT_THAT(the_parser<Inner> | (is_parser_for<char>.with_result<decltype(std::variant<output_span<char>, std::tuple<output_span<char>, output_span<char>>>{})>));
    EXPECT_THAT(the_parser<Inner> | (is_parser_for<wchar_t>.with_result<decltype(std::variant<output_span<wchar_t>, std::tuple<output_span<wchar_t>, output_span<wchar_t>>>{})>));
    EXPECT_THAT(the_parser<Inner> | (is_parser_for<int>.with_result<decltype(std::variant<output_span<int>, std::tuple<output_span<int>, output_span<int>>>{})>));

    EXPECT_THAT(the_parser<P> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<P> | has_family<join_family>);
    EXPECT_THAT(the_parser<P> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<P> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<P> | is_parser_for<int>.with_result<output_span<int>>);

#if __cpp_lib_variant >= 202106L // Fully constexpr std::variant
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abc,??", "abc", ",??"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcd,??", "abc", "d,??"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(",??abc", ",??", "abc"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(" ,??abc"));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abc,??", L"abc", L",??"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcd,??", L"abc", L"d,??"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L",??abc", L",??", L"abc"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L" ,??abc"));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abc,??"), e<int>("abc"), e<int>(",??")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcd,??"), e<int>("abc"), e<int>("d,??")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>(",??abc"), e<int>(",??"), e<int>("abc")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>(" ,??abc")));
#endif
}

} // namespace
} // namespace k3::tok3n::tests
