#include "pch.h"

using L = Literal<"literal">;

TEST("Literal", "Requirements")
{
	assert
		, IsParser<L, LiteralType, std::string_view>
		;
}

TEST("Literal", "Parse 'literal'")
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

TEST("Literal", "Constructible from ascii only")
{
	assert
		, constructible::from<"literal">
		, constructible::from<"lïterål">
		;
}

TEST("Literal", "Parse empty")
{
	assert
		, constructible::from<"">
		, parse<Literal<"">>("anything").success("", "anything")
		, parse<Literal<"">>("").success("", "")
		;
}
