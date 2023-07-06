#include "pch.h"

TEST("ZeroOrMore", "Requirements")
{
	assert
		, IsParser<Zom1, ZeroOrMoreType, std::vector<std::string_view>>
		, IsParser<Zom2, ZeroOrMoreType, std::vector<std::string_view>>
		, IsParser<Zom3, ZeroOrMoreType, std::vector<std::string_view>>
		, IsParser<Zom4, ZeroOrMoreType, std::vector<std::tuple<std::string_view, std::string_view>>>
		;
}

TEST("ZeroOrMore", "Parse ZeroOrMore<Literal>")
{
	assert
		, parse<Zom1>("litera").success({}, "litera")
		, parse<Zom1>("literal").success({ "literal" }, "")
		, parse<Zom1>("literally").success({ "literal" }, "ly")
		, parse<Zom1>("literallitera").success({ "literal" }, "litera")
		, parse<Zom1>("literalliterallitera").success({ "literal", "literal" }, "litera")
		, parse<Zom1>(" literalliterallitera").success({}, " literalliterallitera")
		, parse<Zom1>("").success({}, "")
		;
}
TEST("ZeroOrMore", "Parse ZeroOrMore<OneChar>")
{
	assert
		, parse<Zom2>("abcdef").success({ "a", "b", "c" }, "def")
		, parse<Zom2>("fedcba").success({}, "fedcba")
		, parse<Zom2>("cbabcccbjklmnop").success({ "c", "b", "a", "b", "c", "c", "c", "b" }, "jklmnop")
		, parse<Zom2>("").success({}, "")
		;
}
TEST("ZeroOrMore", "Parse ZeroOrMore<Choice>")
{
	assert
		, parse<Zom3>("abliteralcbliteralcf").success({ "a", "b", "literal", "c", "b", "literal", "c" }, "f")
		, parse<Zom3>("abliteralcblitralcf").success({ "a", "b", "literal", "c", "b" }, "litralcf")
		, parse<Zom3>("literalabacliteral").success({ "literal", "a", "b", "a", "c", "literal" }, "")
		, parse<Zom3>("").success({}, "")
		;
}
TEST("ZeroOrMore", "Parse ZeroOrMore<Sequence>")
{
	assert
		, parse<Zom4>("literalaliteralcliteralcliteralb").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "")
		, parse<Zom4>("literalaliteralcliteralcliteralbliteral").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "literal")
		, parse<Zom4>("aliteralaliteralcliteralbliteral").success({}, "aliteralaliteralcliteralbliteral")
		, parse<Zom4>("").success({}, "")
		;
}
