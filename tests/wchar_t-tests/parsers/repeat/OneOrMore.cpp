#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("OneOrMore");

TEST("OneOrMore", "Requirements")
{
	ASSERT_IS_PARSER(Oom1, OneOrMoreFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Oom2, OneOrMoreFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Oom3, OneOrMoreFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Oom4, OneOrMoreFamily, std::vector<std::tuple<Output<wchar_t>, Output<wchar_t>>>);
}

TEST("OneOrMore", "Parse OneOrMore<AllOf>")
{
	using vec_type = std::vector<Output<wchar_t>>;
	ASSERT_PARSE_FAILURE(Oom1, L"litera");
	ASSERT_PARSE_SUCCESS(Oom1, L"literal", vec_type({ L"literal" }), L"");
	ASSERT_PARSE_SUCCESS(Oom1, L"literally", vec_type({ L"literal" }), L"ly");
	ASSERT_PARSE_SUCCESS(Oom1, L"literallitera", vec_type({ L"literal" }), L"litera");
	ASSERT_PARSE_SUCCESS(Oom1, L"literalliterallitera", vec_type({ L"literal", L"literal" }), L"litera");
	ASSERT_PARSE_FAILURE(Oom1, L" literalliterallitera");
	ASSERT_PARSE_FAILURE(Oom1, L"");
}
TEST("OneOrMore", "Parse OneOrMore<AnyOf>")
{
	using vec_type = std::vector<Output<wchar_t>>;
	ASSERT_PARSE_SUCCESS(Oom2, L"abcdef", vec_type({ L"a", L"b", L"c" }), L"def");
	ASSERT_PARSE_FAILURE(Oom2, L"fedcba");
	ASSERT_PARSE_SUCCESS(Oom2, L"cbabcccbjklmnop", vec_type({ L"c", L"b", L"a", L"b", L"c", L"c", L"c", L"b" }), L"jklmnop");
	ASSERT_PARSE_FAILURE(Oom2, L"");
}
TEST("OneOrMore", "Parse OneOrMore<Choice>")
{
	using vec_type = std::vector<Output<wchar_t>>;
	ASSERT_PARSE_SUCCESS(Oom3, L"abliteralcbliteralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b", L"literal", L"c" }), L"f");
	ASSERT_PARSE_SUCCESS(Oom3, L"abliteralcblitralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b" }), L"litralcf");
	ASSERT_PARSE_SUCCESS(Oom3, L"literalabacliteral", vec_type({ L"literal", L"a", L"b", L"a", L"c", L"literal" }), L"");
	ASSERT_PARSE_FAILURE(Oom3, L"");
}
TEST("OneOrMore", "Parse OneOrMore<Sequence>")
{
	using vec_type = std::vector<std::tuple<Output<wchar_t>, Output<wchar_t>>>;
	ASSERT_PARSE_SUCCESS(Oom4, L"literalaliteralcliteralcliteralb", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"");
	ASSERT_PARSE_SUCCESS(Oom4, L"literalaliteralcliteralcliteralbliteral", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"literal");
	ASSERT_PARSE_FAILURE(Oom4, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Oom4, L"");
}
