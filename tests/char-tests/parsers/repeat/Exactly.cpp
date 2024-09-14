#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("Exactly");

TEST("Exactly", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Exa1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Exa2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Exa3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Exa4, value_type);

	ASSERT_IS_PARSER(Exa1, char, exactly_family, std::array<output_span<char>, 3>);
	ASSERT_IS_PARSER(Exa2, char, exactly_family, std::array<output_span<char>, 5>);
	ASSERT_IS_PARSER(Exa3, char, exactly_family, std::array<output_span<char>, 4>);
	ASSERT_IS_PARSER(Exa4, char, exactly_family, std::array<std::tuple<output_span<char>, output_span<char>>, 2>);

	ASSERT_IS_PARSER(Exa1, wchar_t, exactly_family, std::array<output_span<wchar_t>, 3>);
	ASSERT_IS_PARSER(Exa2, wchar_t, exactly_family, std::array<output_span<wchar_t>, 5>);
	ASSERT_IS_PARSER(Exa3, wchar_t, exactly_family, std::array<output_span<wchar_t>, 4>);
	ASSERT_IS_PARSER(Exa4, wchar_t, exactly_family, std::array<std::tuple<output_span<wchar_t>, output_span<wchar_t>>, 2>);

	ASSERT_IS_PARSER(Exa1, int, exactly_family, std::array<output_span<int>, 3>);
	ASSERT_IS_PARSER(Exa2, int, exactly_family, std::array<output_span<int>, 5>);
	ASSERT_IS_PARSER(Exa3, int, exactly_family, std::array<output_span<int>, 4>);
	ASSERT_IS_PARSER(Exa4, int, exactly_family, std::array<std::tuple<output_span<int>, output_span<int>>, 2>);
}

TEST("Exactly", "Constructibility")
{
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, Any1, index_c<0>);
	ASSERT_PARSER_CONSTRUCTIBLE(Exactly, Any1, index_c<1>);
	ASSERT_PARSER_CONSTRUCTIBLE(Exactly, Any1, index_c<2>);

	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, Any1, integral_constant<0>);
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, Any1, integral_constant<1>);
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, Any1, integral_constant<2>);
}

TEST("Exactly", "Parse Exactly<all_of_parser>")
{
	{
		using array_type = std::array<output_span<char>, 3>;
		ASSERT_PARSE_FAILURE(Exa1, "litera");
		ASSERT_PARSE_FAILURE(Exa1, "literal");
		ASSERT_PARSE_FAILURE(Exa1, "literalliteral");
		ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliteral", array_type({ "literal", "literal", "literal" }), "");
		ASSERT_PARSE_FAILURE(Exa1, " literalliteralliteral");
		ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliteralliteral", array_type({ "literal", "literal", "literal" }), "literal");
		ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliterallyliteral", array_type({ "literal", "literal", "literal" }), "lyliteral");
		ASSERT_PARSE_FAILURE(Exa1, "");
	}

	{
		using array_type = std::array<output_span<wchar_t>, 3>;
		ASSERT_PARSE_FAILURE(Exa1, L"litera");
		ASSERT_PARSE_FAILURE(Exa1, L"literal");
		ASSERT_PARSE_FAILURE(Exa1, L"literalliteral");
		ASSERT_PARSE_SUCCESS(Exa1, L"literalliteralliteral", array_type({ L"literal", L"literal", L"literal" }), L"");
		ASSERT_PARSE_FAILURE(Exa1, L" literalliteralliteral");
		ASSERT_PARSE_SUCCESS(Exa1, L"literalliteralliteralliteral", array_type({ L"literal", L"literal", L"literal" }), L"literal");
		ASSERT_PARSE_SUCCESS(Exa1, L"literalliteralliterallyliteral", array_type({ L"literal", L"literal", L"literal" }), L"lyliteral");
		ASSERT_PARSE_FAILURE(Exa1, L"");
	}

	{
		using array_type = std::array<output_span<int>, 3>;
		ASSERT_PARSE_FAILURE(Exa1, e<int>("litera"));
		ASSERT_PARSE_FAILURE(Exa1, e<int>("literal"));
		ASSERT_PARSE_FAILURE(Exa1, e<int>("literalliteral"));
		ASSERT_PARSE_SUCCESS(Exa1, e<int>("literalliteralliteral"), array_type({ e<int>("literal"), e<int>("literal"), e<int>("literal") }), e<int>());
		ASSERT_PARSE_FAILURE(Exa1, e<int>(" literalliteralliteral"));
		ASSERT_PARSE_SUCCESS(Exa1, e<int>("literalliteralliteralliteral"), array_type({ e<int>("literal"), e<int>("literal"), e<int>("literal") }), e<int>("literal"));
		ASSERT_PARSE_SUCCESS(Exa1, e<int>("literalliteralliterallyliteral"), array_type({ e<int>("literal"), e<int>("literal"), e<int>("literal") }), e<int>("lyliteral"));
		ASSERT_PARSE_FAILURE(Exa1, e<int>());
	}
}
TEST("Exactly", "Parse Exactly<any_of_parser>")
{
	{
		using array_type = std::array<output_span<char>, 5>;
		ASSERT_PARSE_SUCCESS(Exa2, "abcbaa", array_type({ "a", "b", "c", "b", "a" }), "a");
		ASSERT_PARSE_FAILURE(Exa2, "fedcba");
		ASSERT_PARSE_SUCCESS(Exa2, "cbabcccbjklmnop", array_type({ "c", "b", "a", "b", "c" }), "ccbjklmnop");
		ASSERT_PARSE_FAILURE(Exa2, "");
	}

	{
		using array_type = std::array<output_span<wchar_t>, 5>;
		ASSERT_PARSE_SUCCESS(Exa2, L"abcbaa", array_type({ L"a", L"b", L"c", L"b", L"a" }), L"a");
		ASSERT_PARSE_FAILURE(Exa2, L"fedcba");
		ASSERT_PARSE_SUCCESS(Exa2, L"cbabcccbjklmnop", array_type({ L"c", L"b", L"a", L"b", L"c" }), L"ccbjklmnop");
		ASSERT_PARSE_FAILURE(Exa2, L"");
	}

	{
		using array_type = std::array<output_span<int>, 5>;
		ASSERT_PARSE_SUCCESS(Exa2, e<int>("abcbaa"), array_type({ e<int>("a"), e<int>("b"), e<int>("c"), e<int>("b"), e<int>("a") }), e<int>("a"));
		ASSERT_PARSE_FAILURE(Exa2, e<int>("fedcba"));
		ASSERT_PARSE_SUCCESS(Exa2, e<int>("cbabcccbjklmnop"), array_type({ e<int>("c"), e<int>("b"), e<int>("a"), e<int>("b"), e<int>("c") }), e<int>("ccbjklmnop"));
		ASSERT_PARSE_FAILURE(Exa2, e<int>());
	}
}
TEST("Exactly", "Parse Exactly<Choice>")
{
	{
		using array_type = std::array<output_span<char>, 4>;
		ASSERT_PARSE_SUCCESS(Exa3, "abliteralcbliteralcf", array_type({ "a", "b", "literal", "c" }), "bliteralcf");
		ASSERT_PARSE_SUCCESS(Exa3, "abliteralcblitralcf", array_type({ "a", "b", "literal", "c" }), "blitralcf");
		ASSERT_PARSE_SUCCESS(Exa3, "literalabacliteral", array_type({ "literal", "a", "b", "a" }), "cliteral");
		ASSERT_PARSE_FAILURE(Exa3, "");
	}

	{
		using array_type = std::array<output_span<wchar_t>, 4>;
		ASSERT_PARSE_SUCCESS(Exa3, L"abliteralcbliteralcf", array_type({ L"a", L"b", L"literal", L"c" }), L"bliteralcf");
		ASSERT_PARSE_SUCCESS(Exa3, L"abliteralcblitralcf", array_type({ L"a", L"b", L"literal", L"c" }), L"blitralcf");
		ASSERT_PARSE_SUCCESS(Exa3, L"literalabacliteral", array_type({ L"literal", L"a", L"b", L"a" }), L"cliteral");
		ASSERT_PARSE_FAILURE(Exa3, L"");
	}

	{
		using array_type = std::array<output_span<int>, 4>;
		ASSERT_PARSE_SUCCESS(Exa3, e<int>("abliteralcbliteralcf"), array_type({ e<int>("a"), e<int>("b"), e<int>("literal"), e<int>("c") }), e<int>("bliteralcf"));
		ASSERT_PARSE_SUCCESS(Exa3, e<int>("abliteralcblitralcf"), array_type({ e<int>("a"), e<int>("b"), e<int>("literal"), e<int>("c") }), e<int>("blitralcf"));
		ASSERT_PARSE_SUCCESS(Exa3, e<int>("literalabacliteral"), array_type({ e<int>("literal"), e<int>("a"), e<int>("b"), e<int>("a") }), e<int>("cliteral"));
		ASSERT_PARSE_FAILURE(Exa3, e<int>());
	}
}
TEST("Exactly", "Parse Exactly<Sequence>")
{
	{
		using array_type = std::array<std::tuple<output_span<char>, output_span<char>>, 2>;
		ASSERT_PARSE_SUCCESS(Exa4, "literalaliteralcliteralcliteralb", array_type({ {"literal", "a"}, {"literal", "c"} }), "literalcliteralb");
		ASSERT_PARSE_SUCCESS(Exa4, "literalaliteralcliteralcliteralbliteral", array_type({ {"literal", "a"}, {"literal", "c"} }), "literalcliteralbliteral");
		ASSERT_PARSE_FAILURE(Exa4, "aliteralaliteralcliteralbliteral");
		ASSERT_PARSE_FAILURE(Exa4, "");
	}

	{
		using array_type = std::array<std::tuple<output_span<wchar_t>, output_span<wchar_t>>, 2>;
		ASSERT_PARSE_SUCCESS(Exa4, L"literalaliteralcliteralcliteralb", array_type({ {L"literal", L"a"}, {L"literal", L"c"} }), L"literalcliteralb");
		ASSERT_PARSE_SUCCESS(Exa4, L"literalaliteralcliteralcliteralbliteral", array_type({ {L"literal", L"a"}, {L"literal", L"c"} }), L"literalcliteralbliteral");
		ASSERT_PARSE_FAILURE(Exa4, L"aliteralaliteralcliteralbliteral");
		ASSERT_PARSE_FAILURE(Exa4, L"");
	}

	{
		using array_type = std::array<std::tuple<output_span<int>, output_span<int>>, 2>;
		ASSERT_PARSE_SUCCESS(Exa4, e<int>("literalaliteralcliteralcliteralb"), array_type({ {e<int>("literal"), e<int>("a")}, {e<int>("literal"), e<int>("c")} }), e<int>("literalcliteralb"));
		ASSERT_PARSE_SUCCESS(Exa4, e<int>("literalaliteralcliteralcliteralbliteral"), array_type({ {e<int>("literal"), e<int>("a")}, {e<int>("literal"), e<int>("c")} }), e<int>("literalcliteralbliteral"));
		ASSERT_PARSE_FAILURE(Exa4, e<int>("aliteralaliteralcliteralbliteral"));
		ASSERT_PARSE_FAILURE(Exa4, e<int>());
	}
}

TEST("Exactly", "Parse Exactly<void-parser>")
{
	using P = Exactly<ignore_parser<ABC>, index_c<2>>;

	ASSERT_PARSE_SUCCESS_VOID(P, "abcabcabca", "abca");
	ASSERT_PARSE_SUCCESS_VOID(P, "abcabca", "a");
	ASSERT_PARSE_SUCCESS_VOID(P, "abcabc", "");
	ASSERT_PARSE_FAILURE(P, " abcabc");
	ASSERT_PARSE_FAILURE(P, "abcab");
	ASSERT_PARSE_FAILURE(P, "abc");
	ASSERT_PARSE_FAILURE(P, "");

	ASSERT_PARSE_SUCCESS_VOID(P, L"abcabcabca", L"abca");
	ASSERT_PARSE_SUCCESS_VOID(P, L"abcabca", L"a");
	ASSERT_PARSE_SUCCESS_VOID(P, L"abcabc", L"");
	ASSERT_PARSE_FAILURE(P, L" abcabc");
	ASSERT_PARSE_FAILURE(P, L"abcab");
	ASSERT_PARSE_FAILURE(P, L"abc");
	ASSERT_PARSE_FAILURE(P, L"");

	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabcabca"), e<int>("abca"));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabca"), e<int>("a"));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabc"), e<int>(""));
	ASSERT_PARSE_FAILURE(P, e<int>(" abcabc"));
	ASSERT_PARSE_FAILURE(P, e<int>("abcab"));
	ASSERT_PARSE_FAILURE(P, e<int>("abc"));
	ASSERT_PARSE_FAILURE(P, e<int>(""));
}
