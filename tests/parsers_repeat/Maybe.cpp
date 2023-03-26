#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(repeat::Maybe)

using namespace samples::all;

void requirements()
{
	assert
		, Parser<May1>
		, May1::type == MaybeType
		, ParserResultOf<May1>::is<std::optional<std::string_view>>

		, Parser<May2>
		, May2::type == MaybeType
		, ParserResultOf<May2>::is<std::optional<std::string_view>>

		, Parser<May3>
		, May3::type == MaybeType
		, ParserResultOf<May3>::is<std::optional<std::string_view>>

		, Parser<May4>
		, May4::type == MaybeType
		, ParserResultOf<May4>::is<std::optional<std::tuple<std::string_view, std::string_view>>>
		;
}

void parse_Maybe_Literal()
{
	assert
		, parse<May1>("litera").success({}, "litera")
		, parse<May1>("literal").success({ "literal" }, "")
		, parse<May1>("literally").success({ "literal" }, "ly")
		, parse<May1>("literallitera").success({ "literal" }, "litera")
		, parse<May1>("literalliterallitera").success({ "literal" }, "literallitera")
		, parse<May1>(" literalliterallitera").success({}, " literalliterallitera")
		, parse<May1>("").success({}, "")
		;
}
void parse_Maybe_OneChar()
{
	assert
		, parse<May2>("abcdef").success({ "a" }, "bcdef")
		, parse<May2>("fedcba").success({}, "fedcba")
		, parse<May2>("cbabcccbjklmnop").success({ "c" }, "babcccbjklmnop")
		, parse<May2>("").success({}, "")
		;
}
void parse_Maybe_Choice()
{
	assert
		, parse<May3>("abliteralcbliteralcf").success({ "a" }, "bliteralcbliteralcf")
		, parse<May3>("abliteralcblitralcf").success({ "a" }, "bliteralcblitralcf")
		, parse<May3>("literalabacliteral").success({ "literal" }, "abacliteral")
		, parse<May3>("").success({}, "")
		;
}
void parse_Maybe_Sequence()
{
	assert
		, parse<May4>("literalaliteralcliteralcliteralb").success({ {"literal", "a"} }, "literalcliteralcliteralb")
		, parse<May4>("literalaliteralcliteralcliteralbliteral").success({ {"literal", "a"} }, "literalcliteralcliteralbliteral")
		, parse<May4>("aliteralaliteralcliteralbliteral").success({}, "aliteralaliteralcliteralbliteral")
		, parse<May4>("").success({}, "")
		;
}

TOK3N_END_NAMESPACE_TESTS(repeat::Maybe)
#endif
