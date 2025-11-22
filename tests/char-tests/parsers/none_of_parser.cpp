// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

using Single = none_of_parser<TT('a')>;
using Multi  = none_of_parser<TT("abc")>;

FIXTURE("none_of_parser");

TEST("none_of_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Single> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Multi> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Single> | has_family<none_of_family>);
    EXPECT_THAT(the_parser<Multi> | has_family<none_of_family>);

    EXPECT_THAT(the_parser<Single> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Multi> | is_parser_for<char>.with_result<output_span<char>>);

    EXPECT_THAT(the_parser<Single> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Multi> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);

    EXPECT_THAT(the_parser<Single> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Multi> | is_parser_for<int>.with_result<output_span<int>>);
}

TEST("none_of_parser", "Parse single")
{
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING("ab"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING("ba", "b", "a"));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING("abc"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING("Ab", "A", "b"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING("Abc", "A", "bc"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(" abc", " ", "abc"));

    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(L"ab"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(L"ba", L"b", L"a"));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(L"abc"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(L"Ab", L"A", L"b"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(L"Abc", L"A", L"bc"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(L" abc", L" ", L"abc"));

    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(e<int>("ab")));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e<int>("ba"), e<int>("b"), e<int>("a")));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(e<int>("abc")));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e<int>("Ab"), e<int>("A"), e<int>("b")));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e<int>("Abc"), e<int>("A"), e<int>("bc")));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e<int>(" abc"), e<int>(" "), e<int>("abc")));
}

TEST("none_of_parser", "Parse multi")
{
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("abc"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("acb"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("bac"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("bca"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("cab"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("cba"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("ABC", "A", "BC"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("ACB", "A", "CB"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("BAC", "B", "AC"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("BCA", "B", "CA"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("CAB", "C", "AB"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("CBA", "C", "BA"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("dcba", "d", "cba"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("edcba", "e", "dcba"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(" cba", " ", "cba"));

    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"abc"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"acb"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"bac"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"bca"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"cab"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"cba"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"ABC", L"A", L"BC"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"ACB", L"A", L"CB"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"BAC", L"B", L"AC"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"BCA", L"B", L"CA"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"CAB", L"C", L"AB"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"CBA", L"C", L"BA"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"dcba", L"d", L"cba"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"edcba", L"e", L"dcba"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L" cba", L" ", L"cba"));

    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("abc")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("acb")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("bac")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("bca")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("cab")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("cba")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("ABC"), e<int>("A"), e<int>("BC")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("ACB"), e<int>("A"), e<int>("CB")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("BAC"), e<int>("B"), e<int>("AC")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("BCA"), e<int>("B"), e<int>("CA")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("CAB"), e<int>("C"), e<int>("AB")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("CBA"), e<int>("C"), e<int>("BA")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("dcba"), e<int>("d"), e<int>("cba")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("edcba"), e<int>("e"), e<int>("dcba")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>(" cba"), e<int>(" "), e<int>("cba")));
}



TEST("none_of_parser", "Constructible from lexicographically sorted only")
{
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_valid_with<TT("abc")>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<TT("acb")>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<TT("bac")>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<TT("bca")>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<TT("cab")>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<TT("cba")>);
}

TEST("none_of_parser", "Parse empty")
{
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_valid_with<TT("")>);

    EXPECT_THAT(the_parser<none_of_parser<"">> | SUCCEEDS_PARSING("anything", "a", "nything"));
    EXPECT_THAT(the_parser<none_of_parser<"">> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<none_of_parser<L"">> | SUCCEEDS_PARSING(L"anything", L"a", L"nything"));
    EXPECT_THAT(the_parser<none_of_parser<L"">> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<none_of_parser<"">> | SUCCEEDS_PARSING(e<int>("anything"), e<int>("a"), e<int>("nything")));
    EXPECT_THAT(the_parser<none_of_parser<"">> | FAILS_PARSING(e<int>()));
}

} // namespace
} // namespace k3::tok3n::tests
