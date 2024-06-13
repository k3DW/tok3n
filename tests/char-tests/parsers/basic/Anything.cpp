#include "pch.h"
#include "char-tests/samples.h"

FIXTURE("Anything");

TEST("Anything", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Ant1, value_type);

	ASSERT_IS_PARSER(Ant1, char, AnythingFamily, Output<char>);
	ASSERT_IS_PARSER(Ant1, wchar_t, AnythingFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Ant1, int, AnythingFamily, Output<int>);
}

TEST("Anything", "Parse")
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
