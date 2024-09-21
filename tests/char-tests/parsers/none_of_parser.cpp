#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

using Single = none_of_parser<TT('a')>;
using Multi  = none_of_parser<TT("abc")>;

FIXTURE("none_of_parser");

TEST("none_of_parser", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Single, value_type);
	ASSERT_PARSER_VALUE_TYPE(Multi, value_type);

	ASSERT_IS_PARSER(Single, char, none_of_family, output_span<char>);
	ASSERT_IS_PARSER(Multi, char, none_of_family, output_span<char>);

	ASSERT_IS_PARSER(Single, wchar_t, none_of_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Multi, wchar_t, none_of_family, output_span<wchar_t>);

	ASSERT_IS_PARSER(Single, int, none_of_family, output_span<int>);
	ASSERT_IS_PARSER(Multi, int, none_of_family, output_span<int>);
}

TEST("none_of_parser", "Parse single")
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

TEST("none_of_parser", "Parse multi")
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



TEST("none_of_parser", "Constructible from lexicographically sorted only")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(none_of_parser, TT("abc"));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, TT("acb"));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, TT("bac"));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, TT("bca"));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, TT("cab"));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, TT("cba"));
}

TEST("none_of_parser", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(none_of_parser, TT(""));

	ASSERT_PARSE_SUCCESS(none_of_parser<"">, "anything", "a", "nything");
	ASSERT_PARSE_FAILURE(none_of_parser<"">, "");

	ASSERT_PARSE_SUCCESS(none_of_parser<L"">, L"anything", L"a", L"nything");
	ASSERT_PARSE_FAILURE(none_of_parser<L"">, L"");

	ASSERT_PARSE_SUCCESS(none_of_parser<"">, e<int>("anything"), e<int>("a"), e<int>("nything"));
	ASSERT_PARSE_FAILURE(none_of_parser<"">, e<int>());
}
