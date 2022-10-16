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
		;
}

void parse_single()
{
	assert
		, parse<L>("literal").success("literal", "")
		, parse<L>("literally").success("literal", "ly")
		, parse<L>("litera").failure()
		, parse<L>(" literal").failure()
		, parse<L>("LITERAL").failure()
		, parse<L>("LITERALLY").failure()
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
		, not constructible::from<"l�ter�l">
		;
}

void not_constructible_empty()
{
	assert, not constructible::from<"">;
}

TOK3N_END_NAMESPACE_TESTS(basic::Literal)
