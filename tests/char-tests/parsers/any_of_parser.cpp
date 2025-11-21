// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

using Single = any_of_parser<TT('a')>;
using Multi  = any_of_parser<TT("abc")>;

FIXTURE("any_of_parser");

TEST("any_of_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Single> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Multi> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Single> | has_family<any_of_family>);
    EXPECT_THAT(the_parser<Multi> | has_family<any_of_family>);

    EXPECT_THAT(the_parser<Single> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Multi> | is_parser_for<char>.with_result<output_span<char>>);

    EXPECT_THAT(the_parser<Single> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Multi> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);

    EXPECT_THAT(the_parser<Single> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Multi> | is_parser_for<int>.with_result<output_span<int>>);
}

TEST("any_of_parser", "Parse single")
{
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING("ab", "a", "b"));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING("ba"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING("abc", "a", "bc"));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING("Ab"));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING("Abc"));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(" abc"));

    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(L"ab", L"a", L"b"));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(L"ba"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(L"abc", L"a", L"bc"));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(L"Ab"));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(L"Abc"));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(L" abc"));

    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e<int>("ab"), e<int>("a"), e<int>("b")));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(e<int>("ba")));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("a"), e<int>("bc")));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(e<int>("Ab")));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(e<int>("Abc")));
    EXPECT_THAT(the_parser<Single> | FAILS_PARSING(e<int>(" abc")));
}

TEST("any_of_parser", "Parse multi")
{
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("abc", "a", "bc"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("acb", "a", "cb"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("bac", "b", "ac"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("bca", "b", "ca"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("cab", "c", "ab"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("cba", "c", "ba"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("ABC"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("ACB"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("BAC"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("BCA"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("CAB"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("CBA"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING("dcba"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(" cba"));

    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"abc", L"a", L"bc"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"acb", L"a", L"cb"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"bac", L"b", L"ac"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"bca", L"b", L"ca"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"cab", L"c", L"ab"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"cba", L"c", L"ba"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"ABC"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"ACB"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"BAC"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"BCA"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"CAB"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"CBA"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L"dcba"));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(L" cba"));

    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("a"), e<int>("bc")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("acb"), e<int>("a"), e<int>("cb")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("bac"), e<int>("b"), e<int>("ac")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("bca"), e<int>("b"), e<int>("ca")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("cab"), e<int>("c"), e<int>("ab")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("cba"), e<int>("c"), e<int>("ba")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("ABC")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("ACB")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("BAC")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("BCA")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("CAB")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("CBA")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>("dcba")));
    EXPECT_THAT(the_parser<Multi> | FAILS_PARSING(e<int>(" cba")));
}



TEST("any_of_parser", "Constructible from lexicographically sorted only")
{
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_valid_with<TT("abc")>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<TT("acb")>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<TT("bac")>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<TT("bca")>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<TT("cab")>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<TT("cba")>);
}

TEST("any_of_parser", "Parse empty")
{
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_valid_with<TT("")>);

    EXPECT_THAT(the_parser<any_of_parser<"">> | FAILS_PARSING("anything"));
    EXPECT_THAT(the_parser<any_of_parser<"">> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<any_of_parser<L"">> | FAILS_PARSING(L"anything"));
    EXPECT_THAT(the_parser<any_of_parser<L"">> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<any_of_parser<"">> | FAILS_PARSING(e<int>("anything")));
    EXPECT_THAT(the_parser<any_of_parser<"">> | FAILS_PARSING(e<int>()));
}

} // namespace
} // namespace k3::tok3n::tests
