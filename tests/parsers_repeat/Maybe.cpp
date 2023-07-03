#include "pch.h"

static void requirements()
{
	assert
		, IsParser<May1, MaybeType, std::optional<std::string_view>>
		, IsParser<May2, MaybeType, std::optional<std::string_view>>
		, IsParser<May3, MaybeType, std::optional<std::string_view>>
		, IsParser<May4, MaybeType, std::optional<std::tuple<std::string_view, std::string_view>>>
		;
}

static void parse_Maybe_Literal()
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
static void parse_Maybe_OneChar()
{
	assert
		, parse<May2>("abcdef").success({ "a" }, "bcdef")
		, parse<May2>("fedcba").success({}, "fedcba")
		, parse<May2>("cbabcccbjklmnop").success({ "c" }, "babcccbjklmnop")
		, parse<May2>("").success({}, "")
		;
}
static void parse_Maybe_Choice()
{
	assert
		, parse<May3>("abliteralcbliteralcf").success({ "a" }, "bliteralcbliteralcf")
		, parse<May3>("abliteralcblitralcf").success({ "a" }, "bliteralcblitralcf")
		, parse<May3>("literalabacliteral").success({ "literal" }, "abacliteral")
		, parse<May3>("").success({}, "")
		;
}
static void parse_Maybe_Sequence()
{
	assert
		, parse<May4>("literalaliteralcliteralcliteralb").success({ {"literal", "a"} }, "literalcliteralcliteralb")
		, parse<May4>("literalaliteralcliteralcliteralbliteral").success({ {"literal", "a"} }, "literalcliteralcliteralbliteral")
		, parse<May4>("aliteralaliteralcliteralbliteral").success({}, "aliteralaliteralcliteralbliteral")
		, parse<May4>("").success({}, "")
		;
}

void Maybe_tests()
{
	requirements();
	parse_Maybe_Literal();
	parse_Maybe_OneChar();
	parse_Maybe_Choice();
	parse_Maybe_Sequence();
}
