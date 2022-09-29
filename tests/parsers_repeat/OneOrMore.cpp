#include "pch.h"

BEGIN_NAMESPACE_TOK3N(tests::repeat::OneOrMore)

using k3::tok3n::OneOrMore;



using P1 = OneOrMore<Literal<"literal">>;
constexpr P1 p1;

using P2 = OneOrMore<OneChar<"abcde">>;
constexpr P2 p2;

using P3 = OneOrMore<Choice<Literal<"literal">, OneChar<"abcde">>>;
constexpr P3 p3;

using P4 = OneOrMore<Sequence<Literal<"literal">, OneChar<"abcde">>>;
constexpr P4 p4;

void requirements()
{
	assert
		, is_parser<P1>
		, parser_type_of<P1>.is_OneOrMore
		, result_of<P1>.is<std::vector<std::string_view>>
		, P1::parse == p1.parse
		, P1::lookahead == p1.lookahead

		, is_parser<P2>
		, parser_type_of<P2>.is_OneOrMore
		, result_of<P2>.is<std::vector<std::string_view>>
		, P2::parse == p2.parse
		, P2::lookahead == p2.lookahead

		, is_parser<P3>
		, parser_type_of<P3>.is_OneOrMore
		, result_of<P3>.is<std::vector<std::string_view>>
		, P3::parse == p3.parse
		, P3::lookahead == p3.lookahead

		, is_parser<P4>
		, parser_type_of<P4>.is_OneOrMore
		, result_of<P4>.is<std::vector<std::tuple<std::string_view, std::string_view>>>
		, P4::parse == p4.parse
		, P4::lookahead == p4.lookahead
		;
}

void parse_OneOrMore_Literal()
{
	assert
		, parse<P1>("litera").failure("litera")
		, parse<P1>("literal").success({ "literal" }, "")
		, parse<P1>("literally").success({ "literal" }, "ly")
		, parse<P1>("literallitera").success({ "literal" }, "litera")
		, parse<P1>("literalliterallitera").success({ "literal", "literal" }, "litera")
		, parse<P1>(" literalliterallitera").failure(" literalliterallitera")
		;
}
void parse_OneOrMore_OneChar()
{
	assert
		, parse<P2>("abcdef").success({ "a", "b", "c", "d", "e" }, "f")
		, parse<P2>("fedcba").failure("fedcba")
		, parse<P2>("cdebabcccbjklmnop").success({ "c", "d", "e", "b", "a", "b", "c", "c", "c", "b" }, "jklmnop")
		;
}
void parse_OneOrMore_Choice()
{
	assert
		, parse<P3>("abliteralcdliteralef").success({ "a", "b", "literal", "c", "d", "literal", "e" }, "f")
		, parse<P3>("abliteralcdlitralef").success({ "a", "b", "literal", "c", "d" }, "litralef")
		, parse<P3>("literalabadliteral").success({ "literal", "a", "b", "a", "d", "literal" }, "")
		;
}
void parse_OneOrMore_Sequence()
{
	assert
		, parse<P4>("literalaliteralcliteraldliteralb").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "d"}, {"literal", "b"} }, "")
		, parse<P4>("literalaliteralcliteraldliteralbliteral").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "d"}, {"literal", "b"} }, "literal")
		, parse<P4>("aliteralaliteralcliteraldliteral").failure("aliteralaliteralcliteraldliteral")
		;
}

END_NAMESPACE_TOK3N(tests::repeat::OneOrMore)
