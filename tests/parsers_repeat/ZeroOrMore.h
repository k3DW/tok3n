#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(repeat::ZeroOrMore)

using P1 = ZeroOrMore<Literal<"literal">>;
constexpr P1 p1;

using P2 = ZeroOrMore<OneChar<"abcde">>;
constexpr P2 p2;

using P3 = ZeroOrMore<Choice<Literal<"literal">, OneChar<"abcde">>>;
constexpr P3 p3;

using P4 = ZeroOrMore<Sequence<Literal<"literal">, OneChar<"abcde">>>;
constexpr P4 p4;

void requirements()
{
	assert
		, is_parser<P1>
		, parser_type_of<P1>.is_ZeroOrMore
		, result_of<P1>.is<std::vector<std::string_view>>
		, P1::parse == p1.parse
		, P1::lookahead == p1.lookahead

		, is_parser<P2>
		, parser_type_of<P2>.is_ZeroOrMore
		, result_of<P2>.is<std::vector<std::string_view>>
		, P2::parse == p2.parse
		, P2::lookahead == p2.lookahead

		, is_parser<P3>
		, parser_type_of<P3>.is_ZeroOrMore
		, result_of<P3>.is<std::vector<std::string_view>>
		, P3::parse == p3.parse
		, P3::lookahead == p3.lookahead

		, is_parser<P4>
		, parser_type_of<P4>.is_ZeroOrMore
		, result_of<P4>.is<std::vector<std::tuple<std::string_view, std::string_view>>>
		, P4::parse == p4.parse
		, P4::lookahead == p4.lookahead
		;
}

void parse_ZeroOrMore_Literal()
{
	assert
		, parse<P1>("litera").success({}, "litera")
		, parse<P1>("literal").success({ "literal" }, "")
		, parse<P1>("literally").success({ "literal" }, "ly")
		, parse<P1>("literallitera").success({ "literal" }, "litera")
		, parse<P1>("literalliterallitera").success({ "literal", "literal" }, "litera")
		, parse<P1>(" literalliterallitera").success({}, " literalliterallitera")
		;
}
void parse_ZeroOrMore_OneChar()
{
	assert
		, parse<P2>("abcdef").success({ "a", "b", "c", "d", "e" }, "f")
		, parse<P2>("fedcba").success({}, "fedcba")
		, parse<P2>("cdebabcccbjklmnop").success({ "c", "d", "e", "b", "a", "b", "c", "c", "c", "b" }, "jklmnop")
		;
}
void parse_ZeroOrMore_Choice()
{
	assert
		, parse<P3>("abliteralcdliteralef").success({ "a", "b", "literal", "c", "d", "literal", "e" }, "f")
		, parse<P3>("abliteralcdlitralef").success({ "a", "b", "literal", "c", "d" }, "litralef")
		, parse<P3>("literalabadliteral").success({ "literal", "a", "b", "a", "d", "literal" }, "")
		;
}
void parse_ZeroOrMore_Sequence()
{
	assert
		, parse<P4>("literalaliteralcliteraldliteralb").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "d"}, {"literal", "b"} }, "")
		, parse<P4>("literalaliteralcliteraldliteralbliteral").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "d"}, {"literal", "b"} }, "literal")
		, parse<P4>("aliteralaliteralcliteraldliteral").success({}, "aliteralaliteralcliteraldliteral")
		;
}

TOK3N_END_NAMESPACE_TESTS(repeat::ZeroOrMore)
