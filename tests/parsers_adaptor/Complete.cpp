#include "pch.h"

FIXTURE("Complete");

TEST("Complete", "Requirements")
{
	ASSERT_IS_PARSER(Com1, CompleteType, Output<char>);
	ASSERT_IS_PARSER(Com2, CompleteType, Output<char>);
	ASSERT_IS_PARSER(Com3, CompleteType, Output<char>);
	ASSERT_IS_PARSER(Com4, CompleteType, std::tuple<Output<char>, Output<char>>);
	ASSERT_IS_PARSER(Com5, CompleteType, std::optional<std::tuple<Output<char>, Output<char>>>);
	ASSERT_IS_PARSER(Com6, CompleteType, std::vector<std::tuple<Output<char>, Output<char>>>);
	ASSERT_IS_PARSER(Com7, CompleteType, std::vector<std::tuple<Output<char>, Output<char>>>);
}

TEST("Complete", "Complete<Literal>")
{
	ASSERT_PARSE_FAILURE(Com1, "litera");
	ASSERT_PARSE_SUCCESS(Com1, "literal", "literal", "");
	ASSERT_PARSE_FAILURE(Com1, "literally");
	ASSERT_PARSE_FAILURE(Com1, "literallitera");
	ASSERT_PARSE_FAILURE(Com1, "literalliterallitera");
	ASSERT_PARSE_FAILURE(Com1, " literalliterallitera");
	ASSERT_PARSE_FAILURE(Com1, "");
}
TEST("Complete", "Complete<OneChar>")
{
	ASSERT_PARSE_SUCCESS(Com2, "a", "a", "");
	ASSERT_PARSE_SUCCESS(Com2, "b", "b", "");
	ASSERT_PARSE_FAILURE(Com2, "abcdef");
	ASSERT_PARSE_FAILURE(Com2, "fedcba");
	ASSERT_PARSE_FAILURE(Com2, "cbabcccbjklmnop");
	ASSERT_PARSE_FAILURE(Com2, "");
}
TEST("Complete", "Complete<Choice>")
{
	ASSERT_PARSE_FAILURE(Com3, "abliteralcbliteralcf");
	ASSERT_PARSE_FAILURE(Com3, "abliteralcblitralcf");
	ASSERT_PARSE_FAILURE(Com3, "literalabacliteral");
	ASSERT_PARSE_SUCCESS(Com3, "literal", "literal", "");
	ASSERT_PARSE_SUCCESS(Com3, "a", "a", "");
	ASSERT_PARSE_SUCCESS(Com3, "b", "b", "");
	ASSERT_PARSE_FAILURE(Com3, "");
}
TEST("Complete", "Complete<Sequence>")
{
	ASSERT_PARSE_FAILURE(Com4, "literalaliteralcliteralcliteralb");
	ASSERT_PARSE_FAILURE(Com4, "literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com4, "literala", std::tuple("literal", "a"), "");
	ASSERT_PARSE_SUCCESS(Com4, "literalb", std::tuple("literal", "b"), "");
	ASSERT_PARSE_FAILURE(Com4, "literald");
	ASSERT_PARSE_FAILURE(Com4, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Com4, "");
}
TEST("Complete", "Complete<Maybe>")
{
	ASSERT_PARSE_FAILURE(Com5, "literalaliteralcliteralcliteralb");
	ASSERT_PARSE_FAILURE(Com5, "literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com5, "literala", std::optional(std::tuple("literal", "a")), "");
	ASSERT_PARSE_SUCCESS(Com5, "literalb", std::optional(std::tuple("literal", "b")), "");
	ASSERT_PARSE_FAILURE(Com5, "literald");
	ASSERT_PARSE_FAILURE(Com5, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com5, "", std::nullopt, "");
}
TEST("Complete", "Complete<OneOrMore>")
{
	ASSERT_PARSE_SUCCESS(Com6, "literalaliteralcliteralcliteralb", Com6::result_type({ { "literal", "a" }, { "literal", "c" }, { "literal", "c" }, { "literal", "b" } }), "");
	ASSERT_PARSE_FAILURE(Com6, "literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com6, "literala", Com6::result_type({ { "literal", "a" } }), "");
	ASSERT_PARSE_SUCCESS(Com6, "literalb", Com6::result_type({ { "literal", "b" } }), "");
	ASSERT_PARSE_FAILURE(Com6, "literald");
	ASSERT_PARSE_FAILURE(Com6, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Com6, "");
}
TEST("Complete", "Complete<ZeroOrMore>")
{
	ASSERT_PARSE_SUCCESS(Com7, "literalaliteralcliteralcliteralb", Com7::result_type({ { "literal", "a" }, { "literal", "c" }, { "literal", "c" }, { "literal", "b" } }), "");
	ASSERT_PARSE_FAILURE(Com7, "literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com7, "literala", Com7::result_type({ { "literal", "a" } }), "");
	ASSERT_PARSE_SUCCESS(Com7, "literalb", Com7::result_type({ { "literal", "b" } }), "");
	ASSERT_PARSE_FAILURE(Com7, "literald");
	ASSERT_PARSE_FAILURE(Com7, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com7, "", Com7::result_type{}, "");
}
