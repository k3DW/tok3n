// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("anything_parser");

TEST("anything_parser", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Ant1, value_type);

	ASSERT_IS_PARSER(Ant1, char, anything_family, output_span<char>);
	ASSERT_IS_PARSER(Ant1, wchar_t, anything_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Ant1, int, anything_family, output_span<int>);
}

TEST("anything_parser", "Parse")
{
	ASSERT_PARSE_SUCCESS(Ant1, "ab", "a", "b");
	ASSERT_PARSE_SUCCESS(Ant1, "ba", "b", "a");
	ASSERT_PARSE_SUCCESS(Ant1, "abc", "a", "bc");
	ASSERT_PARSE_SUCCESS(Ant1, "Ab", "A", "b");
	ASSERT_PARSE_SUCCESS(Ant1, "Abc", "A", "bc");
	ASSERT_PARSE_SUCCESS(Ant1, " abc", " ", "abc");
	ASSERT_PARSE_FAILURE(Ant1, "");

	ASSERT_PARSE_SUCCESS(Ant1, L"ab", L"a", L"b");
	ASSERT_PARSE_SUCCESS(Ant1, L"ba", L"b", L"a");
	ASSERT_PARSE_SUCCESS(Ant1, L"abc", L"a", L"bc");
	ASSERT_PARSE_SUCCESS(Ant1, L"Ab", L"A", L"b");
	ASSERT_PARSE_SUCCESS(Ant1, L"Abc", L"A", L"bc");
	ASSERT_PARSE_SUCCESS(Ant1, L" abc", L" ", L"abc");
	ASSERT_PARSE_FAILURE(Ant1, L"");

	ASSERT_PARSE_SUCCESS(Ant1, e<int>("ab"), e<int>("a"), e<int>("b"));
	ASSERT_PARSE_SUCCESS(Ant1, e<int>("ba"), e<int>("b"), e<int>("a"));
	ASSERT_PARSE_SUCCESS(Ant1, e<int>("abc"), e<int>("a"), e<int>("bc"));
	ASSERT_PARSE_SUCCESS(Ant1, e<int>("Ab"), e<int>("A"), e<int>("b"));
	ASSERT_PARSE_SUCCESS(Ant1, e<int>("Abc"), e<int>("A"), e<int>("bc"));
	ASSERT_PARSE_SUCCESS(Ant1, e<int>(" abc"), e<int>(" "), e<int>("abc"));
	ASSERT_PARSE_FAILURE(Ant1, e<int>(""));
}
