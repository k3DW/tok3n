#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

using Single = AnyOf<L'a'>;
using Multi  = AnyOf<L"abc">;

FIXTURE("AnyOf");

TEST("AnyOf", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Single, wchar_t);
	ASSERT_PARSER_VALUE_TYPE(Multi, wchar_t);

	ASSERT_IS_PARSER(Single, char, AnyOfFamily, Output<char>);
	ASSERT_IS_PARSER(Multi, char, AnyOfFamily, Output<char>);

	ASSERT_IS_PARSER(Single, wchar_t, AnyOfFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Multi, wchar_t, AnyOfFamily, Output<wchar_t>);

	ASSERT_IS_PARSER(Single, int, AnyOfFamily, Output<int>);
	ASSERT_IS_PARSER(Multi, int, AnyOfFamily, Output<int>);
}

TEST("AnyOf", "Parse single")
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

TEST("AnyOf", "Parse multi")
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



TEST("AnyOf", "Constructible from lexicographically sorted only")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AnyOf, L"abc");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, L"acb");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, L"bac");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, L"bca");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, L"cab");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, L"cba");
}

TEST("AnyOf", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AnyOf, L"");

	ASSERT_PARSE_FAILURE(AnyOf<"">, "anything");
	ASSERT_PARSE_FAILURE(AnyOf<"">, "");

	ASSERT_PARSE_FAILURE(AnyOf<L"">, L"anything");
	ASSERT_PARSE_FAILURE(AnyOf<L"">, L"");

	ASSERT_PARSE_FAILURE(AnyOf<"">, e<int>("anything"));
	ASSERT_PARSE_FAILURE(AnyOf<"">, e<int>());
}
