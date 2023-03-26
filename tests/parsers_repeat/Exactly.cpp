#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(repeat::Exactly)

using namespace samples::all;

void requirements()
{
	assert
		, IsParser<Exa1, ExactlyType>
		, ParserResultOf<Exa1>::is<std::array<std::string_view, 3>>

		, IsParser<Exa2, ExactlyType>
		, ParserResultOf<Exa2>::is<std::array<std::string_view, 5>>

		, IsParser<Exa3, ExactlyType>
		, ParserResultOf<Exa3>::is<std::array<std::string_view, 4>>

		, IsParser<Exa4, ExactlyType>
		, ParserResultOf<Exa4>::is<std::array<std::tuple<std::string_view, std::string_view>, 2>>
		;
}

void constructibility()
{
	using traits::repeat::Exactly::constructible;
	assert
		, not constructible::from<OC1, 0>
		, constructible::from<OC1, 1>
		, constructible::from<OC1, 2>
		;
}

void parse_Exactly_Literal()
{
	assert
		, parse<Exa1>("litera").failure()
		, parse<Exa1>("literal").failure()
		, parse<Exa1>("literalliteral").failure()
		, parse<Exa1>("literalliteralliteral").success({ "literal", "literal", "literal" }, "")
		, parse<Exa1>(" literalliteralliteral").failure()
		, parse<Exa1>("literalliteralliteralliteral").success({ "literal", "literal", "literal" }, "literal")
		, parse<Exa1>("literalliteralliterallyliteral").success({ "literal", "literal", "literal" }, "lyliteral")
		, parse<Exa1>("").failure()
		;
}
void parse_Exactly_OneChar()
{
	assert
		, parse<Exa2>("abcbaa").success({ "a", "b", "c", "b", "a" }, "a")
		, parse<Exa2>("fedcba").failure()
		, parse<Exa2>("cbabcccbjklmnop").success({ "c", "b", "a", "b", "c" }, "ccbjklmnop")
		, parse<Exa2>("").failure()
		;
}
void parse_Exactly_Choice()
{
	assert
		, parse<Exa3>("abliteralcbliteralcf").success({ "a", "b", "literal", "c" }, "bliteralcf")
		, parse<Exa3>("abliteralcblitralcf").success({ "a", "b", "literal", "c" }, "blitralcf")
		, parse<Exa3>("literalabacliteral").success({ "literal", "a", "b", "a" }, "cliteral")
		, parse<Exa3>("").failure()
		;
}
void parse_Exactly_Sequence()
{
	assert
		, parse<Exa4>("literalaliteralcliteralcliteralb").success({{ {"literal", "a"}, {"literal", "c"} }}, "literalcliteralb")
		, parse<Exa4>("literalaliteralcliteralcliteralbliteral").success({{ {"literal", "a"}, {"literal", "c"} }}, "literalcliteralbliteral")
		, parse<Exa4>("aliteralaliteralcliteralbliteral").failure()
		, parse<Exa4>("").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(repeat::Exactly)
#endif
