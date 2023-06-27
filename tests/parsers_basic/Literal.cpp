#include "pch.h"

using L = Literal<"literal">;

inline void requirements()
{
	assert
		, IsParser<L, LiteralType, std::string_view>
		;
}

inline void parse_single()
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

inline void constructible_from_ascii_only()
{
	assert
		, constructible::from<"literal">
		, constructible::from<"lïterål">
		;
}

inline void parse_empty()
{
	assert
		, constructible::from<"">
		, parse<Literal<"">>("anything").success("", "anything")
		, parse<Literal<"">>("").success("", "")
		;
}
