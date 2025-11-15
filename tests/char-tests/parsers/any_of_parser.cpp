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
    ASSERT_PARSER_VALUE_TYPE(Single, value_type);
    ASSERT_PARSER_VALUE_TYPE(Multi, value_type);

    ASSERT_IS_PARSER(Single, char, any_of_family, output_span<char>);
    ASSERT_IS_PARSER(Multi, char, any_of_family, output_span<char>);

    ASSERT_IS_PARSER(Single, wchar_t, any_of_family, output_span<wchar_t>);
    ASSERT_IS_PARSER(Multi, wchar_t, any_of_family, output_span<wchar_t>);

    ASSERT_IS_PARSER(Single, int, any_of_family, output_span<int>);
    ASSERT_IS_PARSER(Multi, int, any_of_family, output_span<int>);
}

TEST("any_of_parser", "Parse single")
{
    ASSERT_PARSE_SUCCESS(Single, "ab", "a", "b");
    ASSERT_PARSE_FAILURE(Single, "ba");
    ASSERT_PARSE_SUCCESS(Single, "abc", "a", "bc");
    ASSERT_PARSE_FAILURE(Single, "Ab");
    ASSERT_PARSE_FAILURE(Single, "Abc");
    ASSERT_PARSE_FAILURE(Single, " abc");

    ASSERT_PARSE_SUCCESS(Single, L"ab", L"a", L"b");
    ASSERT_PARSE_FAILURE(Single, L"ba");
    ASSERT_PARSE_SUCCESS(Single, L"abc", L"a", L"bc");
    ASSERT_PARSE_FAILURE(Single, L"Ab");
    ASSERT_PARSE_FAILURE(Single, L"Abc");
    ASSERT_PARSE_FAILURE(Single, L" abc");

    ASSERT_PARSE_SUCCESS(Single, e<int>("ab"), e<int>("a"), e<int>("b"));
    ASSERT_PARSE_FAILURE(Single, e<int>("ba"));
    ASSERT_PARSE_SUCCESS(Single, e<int>("abc"), e<int>("a"), e<int>("bc"));
    ASSERT_PARSE_FAILURE(Single, e<int>("Ab"));
    ASSERT_PARSE_FAILURE(Single, e<int>("Abc"));
    ASSERT_PARSE_FAILURE(Single, e<int>(" abc"));
}

TEST("any_of_parser", "Parse multi")
{
    ASSERT_PARSE_SUCCESS(Multi, "abc", "a", "bc");
    ASSERT_PARSE_SUCCESS(Multi, "acb", "a", "cb");
    ASSERT_PARSE_SUCCESS(Multi, "bac", "b", "ac");
    ASSERT_PARSE_SUCCESS(Multi, "bca", "b", "ca");
    ASSERT_PARSE_SUCCESS(Multi, "cab", "c", "ab");
    ASSERT_PARSE_SUCCESS(Multi, "cba", "c", "ba");
    ASSERT_PARSE_FAILURE(Multi, "ABC");
    ASSERT_PARSE_FAILURE(Multi, "ACB");
    ASSERT_PARSE_FAILURE(Multi, "BAC");
    ASSERT_PARSE_FAILURE(Multi, "BCA");
    ASSERT_PARSE_FAILURE(Multi, "CAB");
    ASSERT_PARSE_FAILURE(Multi, "CBA");
    ASSERT_PARSE_FAILURE(Multi, "dcba");
    ASSERT_PARSE_FAILURE(Multi, " cba");

    ASSERT_PARSE_SUCCESS(Multi, L"abc", L"a", L"bc");
    ASSERT_PARSE_SUCCESS(Multi, L"acb", L"a", L"cb");
    ASSERT_PARSE_SUCCESS(Multi, L"bac", L"b", L"ac");
    ASSERT_PARSE_SUCCESS(Multi, L"bca", L"b", L"ca");
    ASSERT_PARSE_SUCCESS(Multi, L"cab", L"c", L"ab");
    ASSERT_PARSE_SUCCESS(Multi, L"cba", L"c", L"ba");
    ASSERT_PARSE_FAILURE(Multi, L"ABC");
    ASSERT_PARSE_FAILURE(Multi, L"ACB");
    ASSERT_PARSE_FAILURE(Multi, L"BAC");
    ASSERT_PARSE_FAILURE(Multi, L"BCA");
    ASSERT_PARSE_FAILURE(Multi, L"CAB");
    ASSERT_PARSE_FAILURE(Multi, L"CBA");
    ASSERT_PARSE_FAILURE(Multi, L"dcba");
    ASSERT_PARSE_FAILURE(Multi, L" cba");

    ASSERT_PARSE_SUCCESS(Multi, e<int>("abc"), e<int>("a"), e<int>("bc"));
    ASSERT_PARSE_SUCCESS(Multi, e<int>("acb"), e<int>("a"), e<int>("cb"));
    ASSERT_PARSE_SUCCESS(Multi, e<int>("bac"), e<int>("b"), e<int>("ac"));
    ASSERT_PARSE_SUCCESS(Multi, e<int>("bca"), e<int>("b"), e<int>("ca"));
    ASSERT_PARSE_SUCCESS(Multi, e<int>("cab"), e<int>("c"), e<int>("ab"));
    ASSERT_PARSE_SUCCESS(Multi, e<int>("cba"), e<int>("c"), e<int>("ba"));
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
    ASSERT_BASIC_PARSER_CONSTRUCTIBLE(any_of_parser, TT("abc"));
    ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, TT("acb"));
    ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, TT("bac"));
    ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, TT("bca"));
    ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, TT("cab"));
    ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, TT("cba"));
}

TEST("any_of_parser", "Parse empty")
{
    ASSERT_BASIC_PARSER_CONSTRUCTIBLE(any_of_parser, TT(""));

    ASSERT_PARSE_FAILURE(any_of_parser<"">, "anything");
    ASSERT_PARSE_FAILURE(any_of_parser<"">, "");

    ASSERT_PARSE_FAILURE(any_of_parser<L"">, L"anything");
    ASSERT_PARSE_FAILURE(any_of_parser<L"">, L"");

    ASSERT_PARSE_FAILURE(any_of_parser<"">, e<int>("anything"));
    ASSERT_PARSE_FAILURE(any_of_parser<"">, e<int>());
}

} // namespace
} // namespace k3::tok3n::tests
