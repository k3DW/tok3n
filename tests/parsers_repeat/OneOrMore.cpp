#include "pch.h"

TEST("OneOrMore", "Requirements")
{
	assert
		, IsParser<Oom1, OneOrMoreType, std::vector<std::string_view>>
		, IsParser<Oom2, OneOrMoreType, std::vector<std::string_view>>
		, IsParser<Oom3, OneOrMoreType, std::vector<std::string_view>>
		, IsParser<Oom4, OneOrMoreType, std::vector<std::tuple<std::string_view, std::string_view>>>
		;
}

TEST("OneOrMore", "Parse OneOrMore<Literal>")
{
	using vec_type = std::vector<std::string_view>;
	ASSERT_PARSE_FAILURE(Oom1, "litera");
	ASSERT_PARSE_SUCCESS(Oom1, "literal", vec_type({ "literal" }), "");
	ASSERT_PARSE_SUCCESS(Oom1, "literally", vec_type({ "literal" }), "ly");
	ASSERT_PARSE_SUCCESS(Oom1, "literallitera", vec_type({ "literal" }), "litera");
	ASSERT_PARSE_SUCCESS(Oom1, "literalliterallitera", vec_type({ "literal", "literal" }), "litera");
	ASSERT_PARSE_FAILURE(Oom1, " literalliterallitera");
	ASSERT_PARSE_FAILURE(Oom1, "");
}
TEST("OneOrMore", "Parse OneOrMore<OneChar>")
{
	using vec_type = std::vector<std::string_view>;
	ASSERT_PARSE_SUCCESS(Oom2, "abcdef", vec_type({ "a", "b", "c" }), "def");
	ASSERT_PARSE_FAILURE(Oom2, "fedcba");
	ASSERT_PARSE_SUCCESS(Oom2, "cbabcccbjklmnop", vec_type({ "c", "b", "a", "b", "c", "c", "c", "b" }), "jklmnop");
	ASSERT_PARSE_FAILURE(Oom2, "");
}
TEST("OneOrMore", "Parse OneOrMore<Choice>")
{
	using vec_type = std::vector<std::string_view>;
	ASSERT_PARSE_SUCCESS(Oom3, "abliteralcbliteralcf", vec_type({ "a", "b", "literal", "c", "b", "literal", "c" }), "f");
	ASSERT_PARSE_SUCCESS(Oom3, "abliteralcblitralcf", vec_type({ "a", "b", "literal", "c", "b" }), "litralcf");
	ASSERT_PARSE_SUCCESS(Oom3, "literalabacliteral", vec_type({ "literal", "a", "b", "a", "c", "literal" }), "");
	ASSERT_PARSE_FAILURE(Oom3, "");
}
TEST("OneOrMore", "Parse OneOrMore<Sequence>")
{
	using vec_type = std::vector<std::tuple<std::string_view, std::string_view>>;
	ASSERT_PARSE_SUCCESS(Oom4, "literalaliteralcliteralcliteralb", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "");
	ASSERT_PARSE_SUCCESS(Oom4, "literalaliteralcliteralcliteralbliteral", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "literal");
	ASSERT_PARSE_FAILURE(Oom4, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Oom4, "");
}
