#include "pch.h"
#include "char-tests/samples.h"

using L = AllOf<TT("literal")>;

FIXTURE("AllOf");

TEST("AllOf", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(L, value_type);
	ASSERT_IS_PARSER(L, char, AllOfFamily, Output<char>);
	ASSERT_IS_PARSER(L, wchar_t, AllOfFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(L, int, AllOfFamily, Output<int>);
}

TEST("AllOf", "Parse 'literal'")
{
	ASSERT_PARSE_SUCCESS(L, "literal", "literal", "");
	ASSERT_PARSE_SUCCESS(L, "literally", "literal", "ly");
	ASSERT_PARSE_FAILURE(L, "litera");
	ASSERT_PARSE_FAILURE(L, " literal");
	ASSERT_PARSE_FAILURE(L, "LITERAL");
	ASSERT_PARSE_FAILURE(L, "LITERALLY");

	ASSERT_PARSE_SUCCESS(L, L"literal", L"literal", L"");
	ASSERT_PARSE_SUCCESS(L, L"literally", L"literal", L"ly");
	ASSERT_PARSE_FAILURE(L, L"litera");
	ASSERT_PARSE_FAILURE(L, L" literal");
	ASSERT_PARSE_FAILURE(L, L"LITERAL");
	ASSERT_PARSE_FAILURE(L, L"LITERALLY");

	ASSERT_PARSE_SUCCESS(L, e<int>("literal"), e<int>("literal"), e<int>());
	ASSERT_PARSE_SUCCESS(L, e<int>("literally"), e<int>("literal"), e<int>("ly"));
	ASSERT_PARSE_FAILURE(L, e<int>("litera"));
	ASSERT_PARSE_FAILURE(L, e<int>(" literal"));
	ASSERT_PARSE_FAILURE(L, e<int>("LITERAL"));
	ASSERT_PARSE_FAILURE(L, e<int>("LITERALLY"));
}



TEST("AllOf", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AllOf, TT(""));

	ASSERT_PARSE_SUCCESS(AllOf<"">, "anything", "", "anything");
	ASSERT_PARSE_SUCCESS(AllOf<"">, "", "", "");

	ASSERT_PARSE_SUCCESS(AllOf<L"">, L"anything", L"", L"anything");
	ASSERT_PARSE_SUCCESS(AllOf<L"">, L"", L"", L"");

	ASSERT_PARSE_SUCCESS(AllOf<"">, e<int>("anything"), e<int>(), e<int>("anything"));
	ASSERT_PARSE_SUCCESS(AllOf<"">, e<int>(), e<int>(), e<int>());
}
