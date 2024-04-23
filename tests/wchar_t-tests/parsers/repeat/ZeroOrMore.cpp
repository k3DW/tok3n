#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("ZeroOrMore");

TEST("ZeroOrMore", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Zom1, wchar_t);
	ASSERT_PARSER_VALUE_TYPE(Zom2, wchar_t);
	ASSERT_PARSER_VALUE_TYPE(Zom3, wchar_t);
	ASSERT_PARSER_VALUE_TYPE(Zom4, wchar_t);

	ASSERT_IS_PARSER(Zom1, char, ZeroOrMoreFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Zom2, char, ZeroOrMoreFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Zom3, char, ZeroOrMoreFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Zom4, char, ZeroOrMoreFamily, std::vector<std::tuple<Output<char>, Output<char>>>);

	ASSERT_IS_PARSER(Zom1, wchar_t, ZeroOrMoreFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Zom2, wchar_t, ZeroOrMoreFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Zom3, wchar_t, ZeroOrMoreFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Zom4, wchar_t, ZeroOrMoreFamily, std::vector<std::tuple<Output<wchar_t>, Output<wchar_t>>>);

	ASSERT_IS_PARSER(Zom1, int, ZeroOrMoreFamily, std::vector<Output<int>>);
	ASSERT_IS_PARSER(Zom2, int, ZeroOrMoreFamily, std::vector<Output<int>>);
	ASSERT_IS_PARSER(Zom3, int, ZeroOrMoreFamily, std::vector<Output<int>>);
	ASSERT_IS_PARSER(Zom4, int, ZeroOrMoreFamily, std::vector<std::tuple<Output<int>, Output<int>>>);
}

TEST("ZeroOrMore", "Parse ZeroOrMore<AllOf>")
{
	{
		using vec_type = std::vector<Output<char>>;
		ASSERT_PARSE_SUCCESS(Zom1, "litera", vec_type{}, "litera");
		ASSERT_PARSE_SUCCESS(Zom1, "literal", vec_type({ "literal" }), "");
		ASSERT_PARSE_SUCCESS(Zom1, "literally", vec_type({ "literal" }), "ly");
		ASSERT_PARSE_SUCCESS(Zom1, "literallitera", vec_type({ "literal" }), "litera");
		ASSERT_PARSE_SUCCESS(Zom1, "literalliterallitera", vec_type({ "literal", "literal" }), "litera");
		ASSERT_PARSE_SUCCESS(Zom1, " literalliterallitera", vec_type{}, " literalliterallitera");
		ASSERT_PARSE_SUCCESS(Zom1, "", vec_type{}, "");
	}

	{
		using vec_type = std::vector<Output<wchar_t>>;
		ASSERT_PARSE_SUCCESS(Zom1, L"litera", vec_type{}, L"litera");
		ASSERT_PARSE_SUCCESS(Zom1, L"literal", vec_type({ L"literal" }), L"");
		ASSERT_PARSE_SUCCESS(Zom1, L"literally", vec_type({ L"literal" }), L"ly");
		ASSERT_PARSE_SUCCESS(Zom1, L"literallitera", vec_type({ L"literal" }), L"litera");
		ASSERT_PARSE_SUCCESS(Zom1, L"literalliterallitera", vec_type({ L"literal", L"literal" }), L"litera");
		ASSERT_PARSE_SUCCESS(Zom1, L" literalliterallitera", vec_type{}, L" literalliterallitera");
		ASSERT_PARSE_SUCCESS(Zom1, L"", vec_type{}, L"");
	}

	{
		using vec_type = std::vector<Output<int>>;
		ASSERT_PARSE_SUCCESS(Zom1, e<int>("litera"), vec_type{}, e<int>("litera"));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>("literal"), vec_type({ e<int>("literal") }), e<int>(""));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>("literally"), vec_type({ e<int>("literal") }), e<int>("ly"));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>("literallitera"), vec_type({ e<int>("literal") }), e<int>("litera"));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>("literalliterallitera"), vec_type({ e<int>("literal"), e<int>("literal") }), e<int>("litera"));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>(" literalliterallitera"), vec_type{}, e<int>(" literalliterallitera"));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>(""), vec_type{}, e<int>(""));
	}
}
TEST("ZeroOrMore", "Parse ZeroOrMore<AnyOf>")
{
	{
		using vec_type = std::vector<Output<char>>;
		ASSERT_PARSE_SUCCESS(Zom2, "abcdef", vec_type({ "a", "b", "c" }), "def");
		ASSERT_PARSE_SUCCESS(Zom2, "fedcba", vec_type{}, "fedcba");
		ASSERT_PARSE_SUCCESS(Zom2, "cbabcccbjklmnop", vec_type({ "c", "b", "a", "b", "c", "c", "c", "b" }), "jklmnop");
		ASSERT_PARSE_SUCCESS(Zom2, "", vec_type{}, "");
	}

	{
		using vec_type = std::vector<Output<wchar_t>>;
		ASSERT_PARSE_SUCCESS(Zom2, L"abcdef", vec_type({ L"a", L"b", L"c" }), L"def");
		ASSERT_PARSE_SUCCESS(Zom2, L"fedcba", vec_type{}, L"fedcba");
		ASSERT_PARSE_SUCCESS(Zom2, L"cbabcccbjklmnop", vec_type({ L"c", L"b", L"a", L"b", L"c", L"c", L"c", L"b" }), L"jklmnop");
		ASSERT_PARSE_SUCCESS(Zom2, L"", vec_type{}, L"");
	}

	{
		using vec_type = std::vector<Output<int>>;
		ASSERT_PARSE_SUCCESS(Zom2, e<int>("abcdef"), vec_type({ e<int>("a"), e<int>("b"), e<int>("c") }), e<int>("def"));
		ASSERT_PARSE_SUCCESS(Zom2, e<int>("fedcba"), vec_type{}, e<int>("fedcba"));
		ASSERT_PARSE_SUCCESS(Zom2, e<int>("cbabcccbjklmnop"), vec_type({ e<int>("c"), e<int>("b"), e<int>("a"), e<int>("b"), e<int>("c"), e<int>("c"), e<int>("c"), e<int>("b") }), e<int>("jklmnop"));
		ASSERT_PARSE_SUCCESS(Zom2, e<int>(""), vec_type{}, e<int>(""));
	}
}
TEST("ZeroOrMore", "Parse ZeroOrMore<Choice>")
{
	{
		using vec_type = std::vector<Output<char>>;
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, "abliteralcbliteralcf", vec_type({ "a", "b", "literal", "c", "b", "literal", "c" }), "f");
		ASSERT_PARSE_SUCCESS(Zom3, "abliteralcblitralcf", vec_type({ "a", "b", "literal", "c", "b" }), "litralcf");
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, "literalabacliteral", vec_type({ "literal", "a", "b", "a", "c", "literal" }), "");
		ASSERT_PARSE_SUCCESS(Zom3, "", vec_type{}, "");
	}

	{
		using vec_type = std::vector<Output<wchar_t>>;
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, L"abliteralcbliteralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b", L"literal", L"c" }), L"f");
		ASSERT_PARSE_SUCCESS(Zom3, L"abliteralcblitralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b" }), L"litralcf");
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, L"literalabacliteral", vec_type({ L"literal", L"a", L"b", L"a", L"c", L"literal" }), L"");
		ASSERT_PARSE_SUCCESS(Zom3, L"", vec_type{}, L"");
	}

	{
		using vec_type = std::vector<Output<int>>;
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, e<int>("abliteralcbliteralcf"), vec_type({ e<int>("a"), e<int>("b"), e<int>("literal"), e<int>("c"), e<int>("b"), e<int>("literal"), e<int>("c") }), e<int>("f"));
		ASSERT_PARSE_SUCCESS(Zom3, e<int>("abliteralcblitralcf"), vec_type({ e<int>("a"), e<int>("b"), e<int>("literal"), e<int>("c"), e<int>("b") }), e<int>("litralcf"));
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, e<int>("literalabacliteral"), vec_type({ e<int>("literal"), e<int>("a"), e<int>("b"), e<int>("a"), e<int>("c"), e<int>("literal") }), e<int>(""));
		ASSERT_PARSE_SUCCESS(Zom3, e<int>(""), vec_type{}, e<int>(""));
	}
}
TEST("ZeroOrMore", "Parse ZeroOrMore<Sequence>")
{
	{
		using vec_type = std::vector<std::tuple<Output<char>, Output<char>>>;
		ASSERT_PARSE_SUCCESS(Zom4, "literalaliteralcliteralcliteralb", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "");
		ASSERT_PARSE_SUCCESS(Zom4, "literalaliteralcliteralcliteralbliteral", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "literal");
		ASSERT_PARSE_SUCCESS(Zom4, "aliteralaliteralcliteralbliteral", vec_type{}, "aliteralaliteralcliteralbliteral");
		ASSERT_PARSE_SUCCESS(Zom4, "", vec_type{}, "");
	}

	{
		using vec_type = std::vector<std::tuple<Output<wchar_t>, Output<wchar_t>>>;
		ASSERT_PARSE_SUCCESS(Zom4, L"literalaliteralcliteralcliteralb", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"");
		ASSERT_PARSE_SUCCESS(Zom4, L"literalaliteralcliteralcliteralbliteral", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"literal");
		ASSERT_PARSE_SUCCESS(Zom4, L"aliteralaliteralcliteralbliteral", vec_type{}, L"aliteralaliteralcliteralbliteral");
		ASSERT_PARSE_SUCCESS(Zom4, L"", vec_type{}, L"");
	}

	{
		using vec_type = std::vector<std::tuple<Output<int>, Output<int>>>;
		ASSERT_PARSE_SUCCESS(Zom4, e<int>("literalaliteralcliteralcliteralb"), vec_type({ {e<int>("literal"), e<int>("a")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("b")} }), e<int>(""));
		ASSERT_PARSE_SUCCESS(Zom4, e<int>("literalaliteralcliteralcliteralbliteral"), vec_type({ {e<int>("literal"), e<int>("a")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("b")} }), e<int>("literal"));
		ASSERT_PARSE_SUCCESS(Zom4, e<int>("aliteralaliteralcliteralbliteral"), vec_type{}, e<int>("aliteralaliteralcliteralbliteral"));
		ASSERT_PARSE_SUCCESS(Zom4, e<int>(""), vec_type{}, e<int>(""));
	}
}
