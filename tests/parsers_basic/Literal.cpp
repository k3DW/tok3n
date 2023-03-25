#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(basic::Literal)

using L = Literal<"literal">;

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



using constructible = traits::basic::constructible<Literal>;

void constructible_from_ascii_only()
{
	assert
		, constructible::from<"literal">
		, not constructible::from<"lïterål">
		;
}

void not_constructible_empty()
{
	assert, constructible::from<"">;
}

TOK3N_END_NAMESPACE_TESTS(basic::Literal)
#endif
