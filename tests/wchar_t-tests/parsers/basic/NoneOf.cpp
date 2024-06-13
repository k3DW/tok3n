#include "pch.h"
#include "wchar_t-tests/samples.h"

using Single = NoneOf<L'a'>;
using Multi  = NoneOf<L"abc">;

FIXTURE("NoneOf");

TEST("NoneOf", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Single, wchar_t);
	ASSERT_PARSER_VALUE_TYPE(Multi, wchar_t);

	ASSERT_IS_PARSER(Single, char, NoneOfFamily, Output<char>);
	ASSERT_IS_PARSER(Multi, char, NoneOfFamily, Output<char>);

	ASSERT_IS_PARSER(Single, wchar_t, NoneOfFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Multi, wchar_t, NoneOfFamily, Output<wchar_t>);

	ASSERT_IS_PARSER(Single, int, NoneOfFamily, Output<int>);
	ASSERT_IS_PARSER(Multi, int, NoneOfFamily, Output<int>);
}

TEST("NoneOf", "Parse single")
{
	ASSERT_PARSE_FAILURE(Single, "ab");
	ASSERT_PARSE_SUCCESS(Single, "ba", "b", "a");
	ASSERT_PARSE_FAILURE(Single, "abc");
	ASSERT_PARSE_SUCCESS(Single, "Ab", "A", "b");
	ASSERT_PARSE_SUCCESS(Single, "Abc", "A", "bc");
	ASSERT_PARSE_SUCCESS(Single, " abc", " ", "abc");

	ASSERT_PARSE_FAILURE(Single, L"ab");
	ASSERT_PARSE_SUCCESS(Single, L"ba", L"b", L"a");
	ASSERT_PARSE_FAILURE(Single, L"abc");
	ASSERT_PARSE_SUCCESS(Single, L"Ab", L"A", L"b");
	ASSERT_PARSE_SUCCESS(Single, L"Abc", L"A", L"bc");
	ASSERT_PARSE_SUCCESS(Single, L" abc", L" ", L"abc");

	ASSERT_PARSE_FAILURE(Single, e<int>("ab"));
	ASSERT_PARSE_SUCCESS(Single, e<int>("ba"), e<int>("b"), e<int>("a"));
	ASSERT_PARSE_FAILURE(Single, e<int>("abc"));
	ASSERT_PARSE_SUCCESS(Single, e<int>("Ab"), e<int>("A"), e<int>("b"));
	ASSERT_PARSE_SUCCESS(Single, e<int>("Abc"), e<int>("A"), e<int>("bc"));
	ASSERT_PARSE_SUCCESS(Single, e<int>(" abc"), e<int>(" "), e<int>("abc"));
}

TEST("NoneOf", "Parse multi")
{
	ASSERT_PARSE_FAILURE(Multi, "abc");
	ASSERT_PARSE_FAILURE(Multi, "acb");
	ASSERT_PARSE_FAILURE(Multi, "bac");
	ASSERT_PARSE_FAILURE(Multi, "bca");
	ASSERT_PARSE_FAILURE(Multi, "cab");
	ASSERT_PARSE_FAILURE(Multi, "cba");
	ASSERT_PARSE_SUCCESS(Multi, "ABC", "A", "BC");
	ASSERT_PARSE_SUCCESS(Multi, "ACB", "A", "CB");
	ASSERT_PARSE_SUCCESS(Multi, "BAC", "B", "AC");
	ASSERT_PARSE_SUCCESS(Multi, "BCA", "B", "CA");
	ASSERT_PARSE_SUCCESS(Multi, "CAB", "C", "AB");
	ASSERT_PARSE_SUCCESS(Multi, "CBA", "C", "BA");
	ASSERT_PARSE_SUCCESS(Multi, "dcba", "d", "cba");
	ASSERT_PARSE_SUCCESS(Multi, "edcba", "e", "dcba");
	ASSERT_PARSE_SUCCESS(Multi, " cba", " ", "cba");

	ASSERT_PARSE_FAILURE(Multi, L"abc");
	ASSERT_PARSE_FAILURE(Multi, L"acb");
	ASSERT_PARSE_FAILURE(Multi, L"bac");
	ASSERT_PARSE_FAILURE(Multi, L"bca");
	ASSERT_PARSE_FAILURE(Multi, L"cab");
	ASSERT_PARSE_FAILURE(Multi, L"cba");
	ASSERT_PARSE_SUCCESS(Multi, L"ABC", L"A", L"BC");
	ASSERT_PARSE_SUCCESS(Multi, L"ACB", L"A", L"CB");
	ASSERT_PARSE_SUCCESS(Multi, L"BAC", L"B", L"AC");
	ASSERT_PARSE_SUCCESS(Multi, L"BCA", L"B", L"CA");
	ASSERT_PARSE_SUCCESS(Multi, L"CAB", L"C", L"AB");
	ASSERT_PARSE_SUCCESS(Multi, L"CBA", L"C", L"BA");
	ASSERT_PARSE_SUCCESS(Multi, L"dcba", L"d", L"cba");
	ASSERT_PARSE_SUCCESS(Multi, L"edcba", L"e", L"dcba");
	ASSERT_PARSE_SUCCESS(Multi, L" cba", L" ", L"cba");

	ASSERT_PARSE_FAILURE(Multi, e<int>("abc"));
	ASSERT_PARSE_FAILURE(Multi, e<int>("acb"));
	ASSERT_PARSE_FAILURE(Multi, e<int>("bac"));
	ASSERT_PARSE_FAILURE(Multi, e<int>("bca"));
	ASSERT_PARSE_FAILURE(Multi, e<int>("cab"));
	ASSERT_PARSE_FAILURE(Multi, e<int>("cba"));
	ASSERT_PARSE_SUCCESS(Multi, e<int>("ABC"), e<int>("A"), e<int>("BC"));
	ASSERT_PARSE_SUCCESS(Multi, e<int>("ACB"), e<int>("A"), e<int>("CB"));
	ASSERT_PARSE_SUCCESS(Multi, e<int>("BAC"), e<int>("B"), e<int>("AC"));
	ASSERT_PARSE_SUCCESS(Multi, e<int>("BCA"), e<int>("B"), e<int>("CA"));
	ASSERT_PARSE_SUCCESS(Multi, e<int>("CAB"), e<int>("C"), e<int>("AB"));
	ASSERT_PARSE_SUCCESS(Multi, e<int>("CBA"), e<int>("C"), e<int>("BA"));
	ASSERT_PARSE_SUCCESS(Multi, e<int>("dcba"), e<int>("d"), e<int>("cba"));
	ASSERT_PARSE_SUCCESS(Multi, e<int>("edcba"), e<int>("e"), e<int>("dcba"));
	ASSERT_PARSE_SUCCESS(Multi, e<int>(" cba"), e<int>(" "), e<int>("cba"));
}



TEST("NoneOf", "Constructible from lexicographically sorted only")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(NoneOf, L"abc");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, L"acb");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, L"bac");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, L"bca");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, L"cab");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NoneOf, L"cba");
}

TEST("NoneOf", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(NoneOf, L"");

	ASSERT_PARSE_SUCCESS(NoneOf<"">, "anything", "a", "nything");
	ASSERT_PARSE_FAILURE(NoneOf<"">, "");

	ASSERT_PARSE_SUCCESS(NoneOf<L"">, L"anything", L"a", L"nything");
	ASSERT_PARSE_FAILURE(NoneOf<L"">, L"");

	ASSERT_PARSE_SUCCESS(NoneOf<"">, e<int>("anything"), e<int>("a"), e<int>("nything"));
	ASSERT_PARSE_FAILURE(NoneOf<"">, e<int>());
}
