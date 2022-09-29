#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(repeat::Maybe)

using P1 = Maybe<Literal<"literal">>;
constexpr P1 p1;

using P2 = Maybe<OneChar<"abcde">>;
constexpr P2 p2;

using P3 = Maybe<Choice<Literal<"literal">, OneChar<"abcde">>>;
constexpr P3 p3;

using P4 = Maybe<Sequence<Literal<"literal">, OneChar<"abcde">>>;
constexpr P4 p4;

void requirements()
{
	assert
		, is_parser<P1>
		, parser_type_of<P1>.is_Maybe
		, result_of<P1>.is<std::optional<std::string_view>>
		, P1::parse == p1.parse
		, P1::lookahead == p1.lookahead

		, is_parser<P2>
		, parser_type_of<P2>.is_Maybe
		, result_of<P2>.is<std::optional<std::string_view>>
		, P2::parse == p2.parse
		, P2::lookahead == p2.lookahead

		, is_parser<P3>
		, parser_type_of<P3>.is_Maybe
		, result_of<P3>.is<std::optional<std::string_view>>
		, P3::parse == p3.parse
		, P3::lookahead == p3.lookahead

		, is_parser<P4>
		, parser_type_of<P4>.is_Maybe
		, result_of<P4>.is<std::optional<std::tuple<std::string_view, std::string_view>>>
		, P4::parse == p4.parse
		, P4::lookahead == p4.lookahead
		;
}

void parse_Maybe_Literal()
{
	assert
		, parse<P1>("litera").success({}, "litera")
		, parse<P1>("literal").success({ "literal" }, "")
		, parse<P1>("literally").success({ "literal" }, "ly")
		, parse<P1>("literallitera").success({ "literal" }, "litera")
		, parse<P1>("literalliterallitera").success({ "literal" }, "literallitera")
		, parse<P1>(" literalliterallitera").success({}, " literalliterallitera")
		;
}
void parse_Maybe_OneChar()
{
	assert
		, parse<P2>("abcdef").success({ "a" }, "bcdef")
		, parse<P2>("fedcba").success({}, "fedcba")
		, parse<P2>("cdebabcccbjklmnop").success({ "c" }, "debabcccbjklmnop")
		;
}
void parse_Maybe_Choice()
{
	assert
		, parse<P3>("abliteralcdliteralef").success({ "a" }, "bliteralcdliteralef")
		, parse<P3>("abliteralcdlitralef").success({ "a" }, "bliteralcdlitralef")
		, parse<P3>("literalabadliteral").success({ "literal" }, "abadliteral")
		;
}
void parse_Maybe_Sequence()
{
	assert
		, parse<P4>("literalaliteralcliteraldliteralb").success({ {"literal", "a"} }, "literalcliteraldliteralb")
		, parse<P4>("literalaliteralcliteraldliteralbliteral").success({ {"literal", "a"} }, "literalcliteraldliteralbliteral")
		, parse<P4>("aliteralaliteralcliteraldliteral").success({}, "aliteralaliteralcliteraldliteral")
		;
}

TOK3N_END_NAMESPACE_TESTS(repeat::Maybe)
