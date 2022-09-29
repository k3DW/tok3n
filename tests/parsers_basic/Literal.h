#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(basic::Literal)

using L = Literal<"literal">;
constexpr L l;

void requirements()
{
	assert
		, is_parser<L>
		, parser_type_of<L>.is_Literal
		, result_of<L>.is<std::string_view>
		, L::parse == l.parse
		, L::lookahead == l.lookahead
		;
}

void parse_single()
{
	assert
		, parse<L>("literal").success("literal", "")
		, parse<L>("literally").success("literal", "ly")
		, parse<L>("litera").failure("litera")
		, parse<L>(" literal").failure(" literal")
		, parse<L>("LITERAL").failure("LITERAL")
		, parse<L>("LITERALLY").failure("LITERALLY")
		;
}



struct constructible
{
	template <static_string str> static constexpr bool from = requires { typename Literal<str>; };
};

void constructible_from_ascii_only()
{
	assert
		, constructible::from<"literal">
		, not constructible::from<"lïterål">
		;
}

void not_constructible_empty()
{
	assert, not constructible::from<"">;
}

TOK3N_END_NAMESPACE_TESTS(basic::Literal)
