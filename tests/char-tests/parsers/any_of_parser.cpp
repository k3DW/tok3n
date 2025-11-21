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
    ASSERT_PARSE_FAILURE(Single, "ba");
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING("abc", "a", "bc"));
    ASSERT_PARSE_FAILURE(Single, "Ab");
    ASSERT_PARSE_FAILURE(Single, "Abc");
    ASSERT_PARSE_FAILURE(Single, " abc");

    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(L"ab", L"a", L"b"));
    ASSERT_PARSE_FAILURE(Single, L"ba");
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(L"abc", L"a", L"bc"));
    ASSERT_PARSE_FAILURE(Single, L"Ab");
    ASSERT_PARSE_FAILURE(Single, L"Abc");
    ASSERT_PARSE_FAILURE(Single, L" abc");

    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e<int>("ab"), e<int>("a"), e<int>("b")));
    ASSERT_PARSE_FAILURE(Single, e<int>("ba"));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("a"), e<int>("bc")));
    ASSERT_PARSE_FAILURE(Single, e<int>("Ab"));
    ASSERT_PARSE_FAILURE(Single, e<int>("Abc"));
    ASSERT_PARSE_FAILURE(Single, e<int>(" abc"));
}

TEST("any_of_parser", "Parse multi")
{
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("abc", "a", "bc"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("acb", "a", "cb"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("bac", "b", "ac"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("bca", "b", "ca"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("cab", "c", "ab"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING("cba", "c", "ba"));
    ASSERT_PARSE_FAILURE(Multi, "ABC");
    ASSERT_PARSE_FAILURE(Multi, "ACB");
    ASSERT_PARSE_FAILURE(Multi, "BAC");
    ASSERT_PARSE_FAILURE(Multi, "BCA");
    ASSERT_PARSE_FAILURE(Multi, "CAB");
    ASSERT_PARSE_FAILURE(Multi, "CBA");
    ASSERT_PARSE_FAILURE(Multi, "dcba");
    ASSERT_PARSE_FAILURE(Multi, " cba");

    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"abc", L"a", L"bc"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"acb", L"a", L"cb"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"bac", L"b", L"ac"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"bca", L"b", L"ca"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"cab", L"c", L"ab"));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(L"cba", L"c", L"ba"));
    ASSERT_PARSE_FAILURE(Multi, L"ABC");
    ASSERT_PARSE_FAILURE(Multi, L"ACB");
    ASSERT_PARSE_FAILURE(Multi, L"BAC");
    ASSERT_PARSE_FAILURE(Multi, L"BCA");
    ASSERT_PARSE_FAILURE(Multi, L"CAB");
    ASSERT_PARSE_FAILURE(Multi, L"CBA");
    ASSERT_PARSE_FAILURE(Multi, L"dcba");
    ASSERT_PARSE_FAILURE(Multi, L" cba");

    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("a"), e<int>("bc")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("acb"), e<int>("a"), e<int>("cb")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("bac"), e<int>("b"), e<int>("ac")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("bca"), e<int>("b"), e<int>("ca")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("cab"), e<int>("c"), e<int>("ab")));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e<int>("cba"), e<int>("c"), e<int>("ba")));
    ASSERT_PARSE_FAILURE(Multi, e<int>("ABC"));
    ASSERT_PARSE_FAILURE(Multi, e<int>("ACB"));
    ASSERT_PARSE_FAILURE(Multi, e<int>("BAC"));
    ASSERT_PARSE_FAILURE(Multi, e<int>("BCA"));
    ASSERT_PARSE_FAILURE(Multi, e<int>("CAB"));
    ASSERT_PARSE_FAILURE(Multi, e<int>("CBA"));
    ASSERT_PARSE_FAILURE(Multi, e<int>("dcba"));
    ASSERT_PARSE_FAILURE(Multi, e<int>(" cba"));
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

    ASSERT_PARSE_FAILURE(any_of_parser<"">, "anything");
    ASSERT_PARSE_FAILURE(any_of_parser<"">, "");

    ASSERT_PARSE_FAILURE(any_of_parser<L"">, L"anything");
    ASSERT_PARSE_FAILURE(any_of_parser<L"">, L"");

    ASSERT_PARSE_FAILURE(any_of_parser<"">, e<int>("anything"));
    ASSERT_PARSE_FAILURE(any_of_parser<"">, e<int>());
}

} // namespace
} // namespace k3::tok3n::tests
