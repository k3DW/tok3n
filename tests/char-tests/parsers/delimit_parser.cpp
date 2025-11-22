// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

template <class V>
using vec_type = std::vector<output_span<V>>;

constexpr auto arr_abc = e<int>("abc");
constexpr auto arr_qq = e<int>("??");
constexpr auto arr_comma = e<int>(",");
constexpr auto arr_dot = e<int>(".");
constexpr auto arr_space = e<int>(" ");

FIXTURE("delimit_parser regular");
FIXTURE("delimit_parser keep");

TEST("delimit_parser regular", "Requirements")
{
    EXPECT_THAT(the_parser<Del1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Del2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Del3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Del4> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Del5> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Del6> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Del7> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Del8> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Del1> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Del2> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Del3> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Del4> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Del5> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Del6> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Del7> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Del8> | has_family<delimit_family>);

    EXPECT_THAT(the_parser<Del1> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Del2> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Del3> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Del4> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Del5> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Del6> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Del7> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);
    EXPECT_THAT(the_parser<Del8> | is_parser_for<char>.with_result<std::vector<output_span<char>>>);

    EXPECT_THAT(the_parser<Del1> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Del2> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Del3> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Del4> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Del5> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Del6> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Del7> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);
    EXPECT_THAT(the_parser<Del8> | is_parser_for<wchar_t>.with_result<std::vector<output_span<wchar_t>>>);

    EXPECT_THAT(the_parser<Del1> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Del2> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Del3> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Del4> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Del5> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Del6> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Del7> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
    EXPECT_THAT(the_parser<Del8> | is_parser_for<int>.with_result<std::vector<output_span<int>>>);
}

TEST("delimit_parser keep", "Requirements")
{
    EXPECT_THAT(the_parser<Dek1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Dek2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Dek3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Dek4> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Dek5> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Dek6> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Dek7> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Dek8> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Dek1> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Dek2> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Dek3> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Dek4> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Dek5> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Dek6> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Dek7> | has_family<delimit_family>);
    EXPECT_THAT(the_parser<Dek8> | has_family<delimit_family>);

    EXPECT_THAT(the_parser<Dek1> | (is_parser_for<char>.with_result<std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>>));
    EXPECT_THAT(the_parser<Dek2> | (is_parser_for<char>.with_result<std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>>));
    EXPECT_THAT(the_parser<Dek3> | (is_parser_for<char>.with_result<std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>>));
    EXPECT_THAT(the_parser<Dek4> | (is_parser_for<char>.with_result<std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>>));
    EXPECT_THAT(the_parser<Dek5> | (is_parser_for<char>.with_result<std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>>));
    EXPECT_THAT(the_parser<Dek6> | (is_parser_for<char>.with_result<std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>>));
    EXPECT_THAT(the_parser<Dek7> | (is_parser_for<char>.with_result<std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>>));
    EXPECT_THAT(the_parser<Dek8> | (is_parser_for<char>.with_result<std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>>));

    EXPECT_THAT(the_parser<Dek1> | (is_parser_for<wchar_t>.with_result<std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>>));
    EXPECT_THAT(the_parser<Dek2> | (is_parser_for<wchar_t>.with_result<std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>>));
    EXPECT_THAT(the_parser<Dek3> | (is_parser_for<wchar_t>.with_result<std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>>));
    EXPECT_THAT(the_parser<Dek4> | (is_parser_for<wchar_t>.with_result<std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>>));
    EXPECT_THAT(the_parser<Dek5> | (is_parser_for<wchar_t>.with_result<std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>>));
    EXPECT_THAT(the_parser<Dek6> | (is_parser_for<wchar_t>.with_result<std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>>));
    EXPECT_THAT(the_parser<Dek7> | (is_parser_for<wchar_t>.with_result<std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>>));
    EXPECT_THAT(the_parser<Dek8> | (is_parser_for<wchar_t>.with_result<std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>>));

    EXPECT_THAT(the_parser<Dek1> | (is_parser_for<int>.with_result<std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>>));
    EXPECT_THAT(the_parser<Dek2> | (is_parser_for<int>.with_result<std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>>));
    EXPECT_THAT(the_parser<Dek3> | (is_parser_for<int>.with_result<std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>>));
    EXPECT_THAT(the_parser<Dek4> | (is_parser_for<int>.with_result<std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>>));
    EXPECT_THAT(the_parser<Dek5> | (is_parser_for<int>.with_result<std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>>));
    EXPECT_THAT(the_parser<Dek6> | (is_parser_for<int>.with_result<std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>>));
    EXPECT_THAT(the_parser<Dek7> | (is_parser_for<int>.with_result<std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>>));
    EXPECT_THAT(the_parser<Dek8> | (is_parser_for<int>.with_result<std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>>));
}

TEST("delimit_parser regular", "Parse all")
{
    EXPECT_THAT(the_parser<Del1> | SUCCEEDS_PARSING("abc,abc,abc,,abc,abc,abc", vec_type<char>({ "abc", "abc", "abc" }), ",,abc,abc,abc"));
    EXPECT_THAT(the_parser<Del1> | FAILS_PARSING(",abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Del1> | SUCCEEDS_PARSING("abc ,abc,abc,abc,,abc,abc,abc", vec_type<char>({ "abc" }), " ,abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Del1> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Del2> | SUCCEEDS_PARSING("abc.abc abc .abc.abc abc", vec_type<char>({ "abc", "abc", "abc" }), " .abc.abc abc"));
    EXPECT_THAT(the_parser<Del2> | SUCCEEDS_PARSING("abc abc.abc .abc.abc abc", vec_type<char>({ "abc", "abc", "abc" }), " .abc.abc abc"));
    EXPECT_THAT(the_parser<Del2> | FAILS_PARSING(".abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Del2> | FAILS_PARSING(" abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Del2> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Del3> | SUCCEEDS_PARSING("??,??,??,,??,??,??", vec_type<char>({ "??", "??", "??" }), ",,??,??,??"));
    EXPECT_THAT(the_parser<Del3> | FAILS_PARSING(",??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Del3> | SUCCEEDS_PARSING("?? ,??,??,??,,??,??,??", vec_type<char>({ "??" }), " ,??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Del3> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Del4> | SUCCEEDS_PARSING("??.?? ?? .??.?? ??", vec_type<char>({ "??", "??", "??" }), " .??.?? ??"));
    EXPECT_THAT(the_parser<Del4> | SUCCEEDS_PARSING("?? ??.?? .??.?? ??", vec_type<char>({ "??", "??", "??" }), " .??.?? ??"));
    EXPECT_THAT(the_parser<Del4> | FAILS_PARSING(".?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Del4> | FAILS_PARSING(" ?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Del4> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Del1> | SUCCEEDS_PARSING(L"abc,abc,abc,,abc,abc,abc", vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), L",,abc,abc,abc"));
    EXPECT_THAT(the_parser<Del1> | FAILS_PARSING(L",abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Del1> | SUCCEEDS_PARSING(L"abc ,abc,abc,abc,,abc,abc,abc", vec_type<wchar_t>({ L"abc" }), L" ,abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Del1> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Del2> | SUCCEEDS_PARSING(L"abc.abc abc .abc.abc abc", vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), L" .abc.abc abc"));
    EXPECT_THAT(the_parser<Del2> | SUCCEEDS_PARSING(L"abc abc.abc .abc.abc abc", vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), L" .abc.abc abc"));
    EXPECT_THAT(the_parser<Del2> | FAILS_PARSING(L".abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Del2> | FAILS_PARSING(L" abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Del2> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Del3> | SUCCEEDS_PARSING(L"??,??,??,,??,??,??", vec_type<wchar_t>({ L"??", L"??", L"??" }), L",,??,??,??"));
    EXPECT_THAT(the_parser<Del3> | FAILS_PARSING(L",??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Del3> | SUCCEEDS_PARSING(L"?? ,??,??,??,,??,??,??", vec_type<wchar_t>({ L"??" }), L" ,??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Del3> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Del4> | SUCCEEDS_PARSING(L"??.?? ?? .??.?? ??", vec_type<wchar_t>({ L"??", L"??", L"??" }), L" .??.?? ??"));
    EXPECT_THAT(the_parser<Del4> | SUCCEEDS_PARSING(L"?? ??.?? .??.?? ??", vec_type<wchar_t>({ L"??", L"??", L"??" }), L" .??.?? ??"));
    EXPECT_THAT(the_parser<Del4> | FAILS_PARSING(L".?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Del4> | FAILS_PARSING(L" ?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Del4> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Del1> | SUCCEEDS_PARSING(e<int>("abc,abc,abc,,abc,abc,abc"), vec_type<int>({ arr_abc, arr_abc, arr_abc }), e<int>(",,abc,abc,abc")));
    EXPECT_THAT(the_parser<Del1> | FAILS_PARSING(e<int>(",abc,abc,abc,,abc,abc,abc")));
    EXPECT_THAT(the_parser<Del1> | SUCCEEDS_PARSING(e<int>("abc ,abc,abc,abc,,abc,abc,abc"), vec_type<int>({ arr_abc }), e<int>(" ,abc,abc,abc,,abc,abc,abc")));
    EXPECT_THAT(the_parser<Del1> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Del2> | SUCCEEDS_PARSING(e<int>("abc.abc abc .abc.abc abc"), vec_type<int>({ arr_abc, arr_abc, arr_abc }), e<int>(" .abc.abc abc")));
    EXPECT_THAT(the_parser<Del2> | SUCCEEDS_PARSING(e<int>("abc abc.abc .abc.abc abc"), vec_type<int>({ arr_abc, arr_abc, arr_abc }), e<int>(" .abc.abc abc")));
    EXPECT_THAT(the_parser<Del2> | FAILS_PARSING(e<int>(".abc abc.abc .abc.abc abc")));
    EXPECT_THAT(the_parser<Del2> | FAILS_PARSING(e<int>(" abc abc.abc .abc.abc abc")));
    EXPECT_THAT(the_parser<Del2> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Del3> | SUCCEEDS_PARSING(e<int>("??,??,??,,??,??,??"), vec_type<int>({ arr_qq, arr_qq, arr_qq }), e<int>(",,??,??,??")));
    EXPECT_THAT(the_parser<Del3> | FAILS_PARSING(e<int>(",??,??,??,,??,??,??")));
    EXPECT_THAT(the_parser<Del3> | SUCCEEDS_PARSING(e<int>("?? ,??,??,??,,??,??,??"), vec_type<int>({ arr_qq }), e<int>(" ,??,??,??,,??,??,??")));
    EXPECT_THAT(the_parser<Del3> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Del4> | SUCCEEDS_PARSING(e<int>("??.?? ?? .??.?? ??"), vec_type<int>({ arr_qq, arr_qq, arr_qq }), e<int>(" .??.?? ??")));
    EXPECT_THAT(the_parser<Del4> | SUCCEEDS_PARSING(e<int>("?? ??.?? .??.?? ??"), vec_type<int>({ arr_qq, arr_qq, arr_qq }), e<int>(" .??.?? ??")));
    EXPECT_THAT(the_parser<Del4> | FAILS_PARSING(e<int>(".?? ??.?? .??.?? ??")));
    EXPECT_THAT(the_parser<Del4> | FAILS_PARSING(e<int>(" ?? ??.?? .??.?? ??")));
    EXPECT_THAT(the_parser<Del4> | FAILS_PARSING(e<int>()));
}

TEST("delimit_parser regular", "Parse all inverted")
{
    EXPECT_THAT(the_parser<Del5> | FAILS_PARSING("abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Del5> | SUCCEEDS_PARSING(",abc,abc,abc,,abc,abc,abc", vec_type<char>({ ",", ",", ",", "," }), ",abc,abc,abc"));
    EXPECT_THAT(the_parser<Del5> | FAILS_PARSING("abc ,abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Del5> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Del6> | FAILS_PARSING("abc.abc abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Del6> | FAILS_PARSING("abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Del6> | SUCCEEDS_PARSING(".abc abc.abc .abc.abc abc", vec_type<char>({ ".", " ", ".", " " }), ".abc.abc abc"));
    EXPECT_THAT(the_parser<Del6> | SUCCEEDS_PARSING(" abc abc.abc .abc.abc abc", vec_type<char>({ " ", " ", ".", " " }), ".abc.abc abc"));
    EXPECT_THAT(the_parser<Del6> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Del7> | FAILS_PARSING("??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Del7> | SUCCEEDS_PARSING(",??,??,??,,??,??,??", vec_type<char>({ ",", ",", ",", "," }), ",??,??,??"));
    EXPECT_THAT(the_parser<Del7> | FAILS_PARSING("?? ,??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Del7> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Del8> | FAILS_PARSING("??.?? ?? .??.?? ??"));
    EXPECT_THAT(the_parser<Del8> | FAILS_PARSING("?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Del8> | SUCCEEDS_PARSING(".?? ??.?? .??.?? ??", vec_type<char>({ ".", " ", ".", " " }), ".??.?? ??"));
    EXPECT_THAT(the_parser<Del8> | SUCCEEDS_PARSING(" ?? ??.?? .??.?? ??", vec_type<char>({ " ", " ", ".", " " }), ".??.?? ??"));
    EXPECT_THAT(the_parser<Del8> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Del5> | FAILS_PARSING(L"abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Del5> | SUCCEEDS_PARSING(L",abc,abc,abc,,abc,abc,abc", vec_type<wchar_t>({ L",", L",", L",", L"," }), L",abc,abc,abc"));
    EXPECT_THAT(the_parser<Del5> | FAILS_PARSING(L"abc ,abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Del5> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Del6> | FAILS_PARSING(L"abc.abc abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Del6> | FAILS_PARSING(L"abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Del6> | SUCCEEDS_PARSING(L".abc abc.abc .abc.abc abc", vec_type<wchar_t>({ L".", L" ", L".", L" " }), L".abc.abc abc"));
    EXPECT_THAT(the_parser<Del6> | SUCCEEDS_PARSING(L" abc abc.abc .abc.abc abc", vec_type<wchar_t>({ L" ", L" ", L".", L" " }), L".abc.abc abc"));
    EXPECT_THAT(the_parser<Del6> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Del7> | FAILS_PARSING(L"??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Del7> | SUCCEEDS_PARSING(L",??,??,??,,??,??,??", vec_type<wchar_t>({ L",", L",", L",", L"," }), L",??,??,??"));
    EXPECT_THAT(the_parser<Del7> | FAILS_PARSING(L"?? ,??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Del7> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Del8> | FAILS_PARSING(L"??.?? ?? .??.?? ??"));
    EXPECT_THAT(the_parser<Del8> | FAILS_PARSING(L"?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Del8> | SUCCEEDS_PARSING(L".?? ??.?? .??.?? ??", vec_type<wchar_t>({ L".", L" ", L".", L" " }), L".??.?? ??"));
    EXPECT_THAT(the_parser<Del8> | SUCCEEDS_PARSING(L" ?? ??.?? .??.?? ??", vec_type<wchar_t>({ L" ", L" ", L".", L" " }), L".??.?? ??"));
    EXPECT_THAT(the_parser<Del8> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Del5> | FAILS_PARSING(e<int>("abc,abc,abc,,abc,abc,abc")));
    EXPECT_THAT(the_parser<Del5> | SUCCEEDS_PARSING(e<int>(",abc,abc,abc,,abc,abc,abc"), vec_type<int>({ arr_comma, arr_comma, arr_comma, arr_comma }), e<int>(",abc,abc,abc")));
    EXPECT_THAT(the_parser<Del5> | FAILS_PARSING(e<int>("abc ,abc,abc,abc,,abc,abc,abc")));
    EXPECT_THAT(the_parser<Del5> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Del6> | FAILS_PARSING(e<int>("abc.abc abc .abc.abc abc")));
    EXPECT_THAT(the_parser<Del6> | FAILS_PARSING(e<int>("abc abc.abc .abc.abc abc")));
    EXPECT_THAT(the_parser<Del6> | SUCCEEDS_PARSING(e<int>(".abc abc.abc .abc.abc abc"), vec_type<int>({ arr_dot, arr_space, arr_dot, arr_space }), e<int>(".abc.abc abc")));
    EXPECT_THAT(the_parser<Del6> | SUCCEEDS_PARSING(e<int>(" abc abc.abc .abc.abc abc"), vec_type<int>({ arr_space, arr_space, arr_dot, arr_space }), e<int>(".abc.abc abc")));
    EXPECT_THAT(the_parser<Del6> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Del7> | FAILS_PARSING(e<int>("??,??,??,,??,??,??")));
    EXPECT_THAT(the_parser<Del7> | SUCCEEDS_PARSING(e<int>(",??,??,??,,??,??,??"), vec_type<int>({ arr_comma, arr_comma, arr_comma, arr_comma }), e<int>(",??,??,??")));
    EXPECT_THAT(the_parser<Del7> | FAILS_PARSING(e<int>("?? ,??,??,??,,??,??,??")));
    EXPECT_THAT(the_parser<Del7> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Del8> | FAILS_PARSING(e<int>("??.?? ?? .??.?? ??")));
    EXPECT_THAT(the_parser<Del8> | FAILS_PARSING(e<int>("?? ??.?? .??.?? ??")));
    EXPECT_THAT(the_parser<Del8> | SUCCEEDS_PARSING(e<int>(".?? ??.?? .??.?? ??"), vec_type<int>({ arr_dot, arr_space, arr_dot, arr_space }), e<int>(".??.?? ??")));
    EXPECT_THAT(the_parser<Del8> | SUCCEEDS_PARSING(e<int>(" ?? ??.?? .??.?? ??"), vec_type<int>({ arr_space, arr_space, arr_dot, arr_space }), e<int>(".??.?? ??")));
    EXPECT_THAT(the_parser<Del8> | FAILS_PARSING(e<int>()));
}

TEST("delimit_parser keep", "Parse all")
{
    EXPECT_THAT(the_parser<Dek1> | SUCCEEDS_PARSING("abc,abc,abc,,abc,abc,abc", std::pair(vec_type<char>({ "abc", "abc", "abc" }), vec_type<char>({ ",", "," })), ",,abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek1> | FAILS_PARSING(",abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek1> | SUCCEEDS_PARSING("abc ,abc,abc,abc,,abc,abc,abc", std::pair(vec_type<char>({ "abc" }), vec_type<char>{}), " ,abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek1> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Dek2> | SUCCEEDS_PARSING("abc.abc abc .abc.abc abc", std::pair(vec_type<char>({ "abc", "abc", "abc" }), vec_type<char>({ ".", " " })), " .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek2> | SUCCEEDS_PARSING("abc abc.abc .abc.abc abc", std::pair(vec_type<char>({ "abc", "abc", "abc" }), vec_type<char>({ " ", "." })), " .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek2> | FAILS_PARSING(".abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek2> | FAILS_PARSING(" abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek2> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Dek3> | SUCCEEDS_PARSING("??,??,??,,??,??,??", std::pair(vec_type<char>({ "??", "??", "??" }), vec_type<char>({ ",", "," })), ",,??,??,??"));
    EXPECT_THAT(the_parser<Dek3> | FAILS_PARSING(",??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Dek3> | SUCCEEDS_PARSING("?? ,??,??,??,,??,??,??", std::pair(vec_type<char>({ "??" }), vec_type<char>{}), " ,??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Dek3> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Dek4> | SUCCEEDS_PARSING("??.?? ?? .??.?? ??", std::pair(vec_type<char>({ "??", "??", "??" }), vec_type<char>({ ".", " " })), " .??.?? ??"));
    EXPECT_THAT(the_parser<Dek4> | SUCCEEDS_PARSING("?? ??.?? .??.?? ??", std::pair(vec_type<char>({ "??", "??", "??" }), vec_type<char>({ " ", "." })), " .??.?? ??"));
    EXPECT_THAT(the_parser<Dek4> | FAILS_PARSING(".?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Dek4> | FAILS_PARSING(" ?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Dek4> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Dek1> | SUCCEEDS_PARSING(L"abc,abc,abc,,abc,abc,abc", std::pair(vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), vec_type<wchar_t>({ L",", L"," })), L",,abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek1> | FAILS_PARSING(L",abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek1> | SUCCEEDS_PARSING(L"abc ,abc,abc,abc,,abc,abc,abc", std::pair(vec_type<wchar_t>({ L"abc" }), vec_type<wchar_t>{}), L" ,abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek1> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Dek2> | SUCCEEDS_PARSING(L"abc.abc abc .abc.abc abc", std::pair(vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), vec_type<wchar_t>({ L".", L" " })), L" .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek2> | SUCCEEDS_PARSING(L"abc abc.abc .abc.abc abc", std::pair(vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), vec_type<wchar_t>({ L" ", L"." })), L" .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek2> | FAILS_PARSING(L".abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek2> | FAILS_PARSING(L" abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek2> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Dek3> | SUCCEEDS_PARSING(L"??,??,??,,??,??,??", std::pair(vec_type<wchar_t>({ L"??", L"??", L"??" }), vec_type<wchar_t>({ L",", L"," })), L",,??,??,??"));
    EXPECT_THAT(the_parser<Dek3> | FAILS_PARSING(L",??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Dek3> | SUCCEEDS_PARSING(L"?? ,??,??,??,,??,??,??", std::pair(vec_type<wchar_t>({ L"??" }), vec_type<wchar_t>{}), L" ,??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Dek3> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Dek4> | SUCCEEDS_PARSING(L"??.?? ?? .??.?? ??", std::pair(vec_type<wchar_t>({ L"??", L"??", L"??" }), vec_type<wchar_t>({ L".", L" " })), L" .??.?? ??"));
    EXPECT_THAT(the_parser<Dek4> | SUCCEEDS_PARSING(L"?? ??.?? .??.?? ??", std::pair(vec_type<wchar_t>({ L"??", L"??", L"??" }), vec_type<wchar_t>({ L" ", L"." })), L" .??.?? ??"));
    EXPECT_THAT(the_parser<Dek4> | FAILS_PARSING(L".?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Dek4> | FAILS_PARSING(L" ?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Dek4> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Dek1> | SUCCEEDS_PARSING(e<int>("abc,abc,abc,,abc,abc,abc"), std::pair(vec_type<int>({ arr_abc, arr_abc, arr_abc }), vec_type<int>({ arr_comma, arr_comma })), e<int>(",,abc,abc,abc")));
    EXPECT_THAT(the_parser<Dek1> | FAILS_PARSING(e<int>(",abc,abc,abc,,abc,abc,abc")));
    EXPECT_THAT(the_parser<Dek1> | SUCCEEDS_PARSING(e<int>("abc ,abc,abc,abc,,abc,abc,abc"), std::pair(vec_type<int>({ arr_abc }), vec_type<int>{}), e<int>(" ,abc,abc,abc,,abc,abc,abc")));
    EXPECT_THAT(the_parser<Dek1> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Dek2> | SUCCEEDS_PARSING(e<int>("abc.abc abc .abc.abc abc"), std::pair(vec_type<int>({ arr_abc, arr_abc, arr_abc }), vec_type<int>({ arr_dot, arr_space })), e<int>(" .abc.abc abc")));
    EXPECT_THAT(the_parser<Dek2> | SUCCEEDS_PARSING(e<int>("abc abc.abc .abc.abc abc"), std::pair(vec_type<int>({ arr_abc, arr_abc, arr_abc }), vec_type<int>({ arr_space, arr_dot })), e<int>(" .abc.abc abc")));
    EXPECT_THAT(the_parser<Dek2> | FAILS_PARSING(e<int>(".abc abc.abc .abc.abc abc")));
    EXPECT_THAT(the_parser<Dek2> | FAILS_PARSING(e<int>(" abc abc.abc .abc.abc abc")));
    EXPECT_THAT(the_parser<Dek2> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Dek3> | SUCCEEDS_PARSING(e<int>("??,??,??,,??,??,??"), std::pair(vec_type<int>({ arr_qq, arr_qq, arr_qq }), vec_type<int>({ arr_comma, arr_comma })), e<int>(",,??,??,??")));
    EXPECT_THAT(the_parser<Dek3> | FAILS_PARSING(e<int>(",??,??,??,,??,??,??")));
    EXPECT_THAT(the_parser<Dek3> | SUCCEEDS_PARSING(e<int>("?? ,??,??,??,,??,??,??"), std::pair(vec_type<int>({ arr_qq }), vec_type<int>{}), e<int>(" ,??,??,??,,??,??,??")));
    EXPECT_THAT(the_parser<Dek3> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Dek4> | SUCCEEDS_PARSING(e<int>("??.?? ?? .??.?? ??"), std::pair(vec_type<int>({ arr_qq, arr_qq, arr_qq }), vec_type<int>({ arr_dot, arr_space })), e<int>(" .??.?? ??")));
    EXPECT_THAT(the_parser<Dek4> | SUCCEEDS_PARSING(e<int>("?? ??.?? .??.?? ??"), std::pair(vec_type<int>({ arr_qq, arr_qq, arr_qq }), vec_type<int>({ arr_space, arr_dot })), e<int>(" .??.?? ??")));
    EXPECT_THAT(the_parser<Dek4> | FAILS_PARSING(e<int>(".?? ??.?? .??.?? ??")));
    EXPECT_THAT(the_parser<Dek4> | FAILS_PARSING(e<int>(" ?? ??.?? .??.?? ??")));
    EXPECT_THAT(the_parser<Dek4> | FAILS_PARSING(e<int>()));
}

TEST("delimit_parser keep", "Parse all inverted")
{
    EXPECT_THAT(the_parser<Dek5> | FAILS_PARSING("abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek5> | SUCCEEDS_PARSING(",abc,abc,abc,,abc,abc,abc", std::pair(vec_type<char>({ ",", ",", ",", ","}), vec_type<char>({ "abc", "abc", "abc" })), ",abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek5> | FAILS_PARSING("abc ,abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek5> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Dek6> | FAILS_PARSING("abc.abc abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek6> | FAILS_PARSING("abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek6> | SUCCEEDS_PARSING(".abc abc.abc .abc.abc abc", std::pair(vec_type<char>({ ".", " ", ".", " "}), vec_type<char>({ "abc", "abc", "abc" })), ".abc.abc abc"));
    EXPECT_THAT(the_parser<Dek6> | SUCCEEDS_PARSING(" abc abc.abc .abc.abc abc", std::pair(vec_type<char>({ " ", " ", ".", " "}), vec_type<char>({ "abc", "abc", "abc" })), ".abc.abc abc"));
    EXPECT_THAT(the_parser<Dek6> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Dek7> | FAILS_PARSING("??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Dek7> | SUCCEEDS_PARSING(",??,??,??,,??,??,??", std::pair(vec_type<char>({ ",", ",", ",", ","}), vec_type<char>({ "??", "??", "??" })), ",??,??,??"));
    EXPECT_THAT(the_parser<Dek7> | FAILS_PARSING("?? ,??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Dek7> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Dek8> | FAILS_PARSING("??.?? ?? .??.?? ??"));
    EXPECT_THAT(the_parser<Dek8> | FAILS_PARSING("?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Dek8> | SUCCEEDS_PARSING(".?? ??.?? .??.?? ??", std::pair(vec_type<char>({ ".", " ", ".", " "}), vec_type<char>({ "??", "??", "??" })), ".??.?? ??"));
    EXPECT_THAT(the_parser<Dek8> | SUCCEEDS_PARSING(" ?? ??.?? .??.?? ??", std::pair(vec_type<char>({ " ", " ", ".", " "}), vec_type<char>({ "??", "??", "??" })), ".??.?? ??"));
    EXPECT_THAT(the_parser<Dek8> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Dek5> | FAILS_PARSING(L"abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek5> | SUCCEEDS_PARSING(L",abc,abc,abc,,abc,abc,abc", std::pair(vec_type<wchar_t>({ L",", L",", L",", L"," }), vec_type<wchar_t>({ L"abc", L"abc", L"abc" })), L",abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek5> | FAILS_PARSING(L"abc ,abc,abc,abc,,abc,abc,abc"));
    EXPECT_THAT(the_parser<Dek5> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Dek6> | FAILS_PARSING(L"abc.abc abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek6> | FAILS_PARSING(L"abc abc.abc .abc.abc abc"));
    EXPECT_THAT(the_parser<Dek6> | SUCCEEDS_PARSING(L".abc abc.abc .abc.abc abc", std::pair(vec_type<wchar_t>({ L".", L" ", L".", L" " }), vec_type<wchar_t>({ L"abc", L"abc", L"abc" })), L".abc.abc abc"));
    EXPECT_THAT(the_parser<Dek6> | SUCCEEDS_PARSING(L" abc abc.abc .abc.abc abc", std::pair(vec_type<wchar_t>({ L" ", L" ", L".", L" " }), vec_type<wchar_t>({ L"abc", L"abc", L"abc" })), L".abc.abc abc"));
    EXPECT_THAT(the_parser<Dek6> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Dek7> | FAILS_PARSING(L"??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Dek7> | SUCCEEDS_PARSING(L",??,??,??,,??,??,??", std::pair(vec_type<wchar_t>({ L",", L",", L",", L"," }), vec_type<wchar_t>({ L"??", L"??", L"??" })), L",??,??,??"));
    EXPECT_THAT(the_parser<Dek7> | FAILS_PARSING(L"?? ,??,??,??,,??,??,??"));
    EXPECT_THAT(the_parser<Dek7> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Dek8> | FAILS_PARSING(L"??.?? ?? .??.?? ??"));
    EXPECT_THAT(the_parser<Dek8> | FAILS_PARSING(L"?? ??.?? .??.?? ??"));
    EXPECT_THAT(the_parser<Dek8> | SUCCEEDS_PARSING(L".?? ??.?? .??.?? ??", std::pair(vec_type<wchar_t>({ L".", L" ", L".", L" " }), vec_type<wchar_t>({ L"??", L"??", L"??" })), L".??.?? ??"));
    EXPECT_THAT(the_parser<Dek8> | SUCCEEDS_PARSING(L" ?? ??.?? .??.?? ??", std::pair(vec_type<wchar_t>({ L" ", L" ", L".", L" " }), vec_type<wchar_t>({ L"??", L"??", L"??" })), L".??.?? ??"));
    EXPECT_THAT(the_parser<Dek8> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Dek5> | FAILS_PARSING(e<int>("abc,abc,abc,,abc,abc,abc")));
    EXPECT_THAT(the_parser<Dek5> | SUCCEEDS_PARSING(e<int>(",abc,abc,abc,,abc,abc,abc"), std::pair(vec_type<int>({ arr_comma, arr_comma, arr_comma, arr_comma }), vec_type<int>({ arr_abc, arr_abc, arr_abc })), e<int>(",abc,abc,abc")));
    EXPECT_THAT(the_parser<Dek5> | FAILS_PARSING(e<int>("abc ,abc,abc,abc,,abc,abc,abc")));
    EXPECT_THAT(the_parser<Dek5> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Dek6> | FAILS_PARSING(e<int>("abc.abc abc .abc.abc abc")));
    EXPECT_THAT(the_parser<Dek6> | FAILS_PARSING(e<int>("abc abc.abc .abc.abc abc")));
    EXPECT_THAT(the_parser<Dek6> | SUCCEEDS_PARSING(e<int>(".abc abc.abc .abc.abc abc"), std::pair(vec_type<int>({ arr_dot, arr_space, arr_dot, arr_space }), vec_type<int>({ arr_abc, arr_abc, arr_abc })), e<int>(".abc.abc abc")));
    EXPECT_THAT(the_parser<Dek6> | SUCCEEDS_PARSING(e<int>(" abc abc.abc .abc.abc abc"), std::pair(vec_type<int>({ arr_space, arr_space, arr_dot, arr_space }), vec_type<int>({ arr_abc, arr_abc, arr_abc })), e<int>(".abc.abc abc")));
    EXPECT_THAT(the_parser<Dek6> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Dek7> | FAILS_PARSING(e<int>("??,??,??,,??,??,??")));
    EXPECT_THAT(the_parser<Dek7> | SUCCEEDS_PARSING(e<int>(",??,??,??,,??,??,??"), std::pair(vec_type<int>({ arr_comma, arr_comma, arr_comma, arr_comma }), vec_type<int>({ arr_qq, arr_qq, arr_qq })), e<int>(",??,??,??")));
    EXPECT_THAT(the_parser<Dek7> | FAILS_PARSING(e<int>("?? ,??,??,??,,??,??,??")));
    EXPECT_THAT(the_parser<Dek7> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Dek8> | FAILS_PARSING(e<int>("??.?? ?? .??.?? ??")));
    EXPECT_THAT(the_parser<Dek8> | FAILS_PARSING(e<int>("?? ??.?? .??.?? ??")));
    EXPECT_THAT(the_parser<Dek8> | SUCCEEDS_PARSING(e<int>(".?? ??.?? .??.?? ??"), std::pair(vec_type<int>({ arr_dot, arr_space, arr_dot, arr_space }), vec_type<int>({ arr_qq, arr_qq, arr_qq })), e<int>(".??.?? ??")));
    EXPECT_THAT(the_parser<Dek8> | SUCCEEDS_PARSING(e<int>(" ?? ??.?? .??.?? ??"), std::pair(vec_type<int>({ arr_space, arr_space, arr_dot, arr_space }), vec_type<int>({ arr_qq, arr_qq, arr_qq })), e<int>(".??.?? ??")));
    EXPECT_THAT(the_parser<Dek8> | FAILS_PARSING(e<int>()));
}

TEST("delimit_parser regular", "Parse delimit_parser<void-parser>")
{
    using P = delimit_parser<ignore_parser<ABC>, ignore_parser<Comma>>;

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abcabcabca", "abcabca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abc,abcabca", "abca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abc,abc,abca", "a"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(",abc,abc,abca"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(" abcabc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abcab", "ab"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID("abc", ""));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abcabcabca", L"abcabca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abc,abcabca", L"abca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abc,abc,abca", L"a"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L",abc,abc,abca"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L" abcabc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abcab", L"ab"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(L"abc", L""));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abcabcabca"), e<int>("abcabca")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abc,abcabca"), e<int>("abca")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abc,abc,abca"), e<int>("a")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>(",abc,abc,abca")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>(" abcabc")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abcab"), e<int>("ab")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING_VOID(e<int>("abc"), e<int>("")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>("")));
}

TEST("delimit_parser keep", "Parse delimit_parser<void-parser>")
{
    using P = delimit_parser<ignore_parser<ABC>, Comma>;

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcabcabca", vec_type<char>({}), "abcabca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abc,abcabca", vec_type<char>({ "," }), "abca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abc,abc,abca", vec_type<char>({ ",", "," }), "a"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(",abc,abc,abca"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(" abcabc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abcab", vec_type<char>({}), "ab"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abc", vec_type<char>({}), ""));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcabcabca", vec_type<wchar_t>({}), L"abcabca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abc,abcabca", vec_type<wchar_t>({ L"," }), L"abca"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abc,abc,abca", vec_type<wchar_t>({ L",", L"," }), L"a"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L",abc,abc,abca"));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L" abcabc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abcab", vec_type<wchar_t>({}), L"ab"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abc", vec_type<wchar_t>({}), L""));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcabcabca"), vec_type<int>({}), e<int>("abcabca")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abc,abcabca"), vec_type<int>({ arr_comma }), e<int>("abca")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abc,abc,abca"), vec_type<int>({ arr_comma, arr_comma }), e<int>("a")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>(",abc,abc,abca")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>(" abcabc")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abcab"), vec_type<int>({}), e<int>("ab")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abc"), vec_type<int>({}), e<int>("")));
    EXPECT_THAT(the_parser<P> | FAILS_PARSING(e<int>("")));
}

} // namespace
} // namespace k3::tok3n::tests
