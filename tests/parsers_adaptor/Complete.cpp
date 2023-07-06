#include "pch.h"

TEST("Complete", "Requirements")
{
	assert
		, IsParser<Com1, CompleteType, std::string_view>
		, IsParser<Com2, CompleteType, std::string_view>
		, IsParser<Com3, CompleteType, std::string_view>
		, IsParser<Com4, CompleteType, std::tuple<std::string_view, std::string_view>>
		, IsParser<Com5, CompleteType, std::optional<std::tuple<std::string_view, std::string_view>>>
		;
}

TEST("Complete", "Complete<Literal>")
{
	assert
		, parse<Com1>("litera").failure()
		, parse<Com1>("literal").success({ "literal" }, "")
		, parse<Com1>("literally").failure()
		, parse<Com1>("literallitera").failure()
		, parse<Com1>("literalliterallitera").failure()
		, parse<Com1>(" literalliterallitera").failure()
		, parse<Com1>("").failure()
		;
}
TEST("Complete", "Complete<OneChar>")
{
	assert
		, parse<Com2>("a").success({ "a" }, "")
		, parse<Com2>("b").success({ "b" }, "")
		, parse<Com2>("abcdef").failure()
		, parse<Com2>("fedcba").failure()
		, parse<Com2>("cbabcccbjklmnop").failure()
		, parse<Com2>("").failure()
		;
}
TEST("Complete", "Complete<Choice>")
{
	assert
		, parse<Com3>("abliteralcbliteralcf").failure()
		, parse<Com3>("abliteralcblitralcf").failure()
		, parse<Com3>("literalabacliteral").failure()
		, parse<Com3>("literal").success({ "literal" }, "")
		, parse<Com3>("a").success({ "a" }, "")
		, parse<Com3>("b").success({ "b" }, "")
		, parse<Com3>("").failure()
		;
}
TEST("Complete", "Complete<Sequence>")
{
	assert
		, parse<Com4>("literalaliteralcliteralcliteralb").failure()
		, parse<Com4>("literalaliteralcliteralcliteralbliteral").failure()
		, parse<Com4>("literala").success({ "literal", "a" }, "")
		, parse<Com4>("literalb").success({ "literal", "b" }, "")
		, parse<Com4>("literald").failure()
		, parse<Com4>("aliteralaliteralcliteralbliteral").failure()
		, parse<Com4>("").failure()
		;
}
TEST("Complete", "Complete<Maybe>")
{
	assert
		, parse<Com5>("literalaliteralcliteralcliteralb").failure()
		, parse<Com5>("literalaliteralcliteralcliteralbliteral").failure()
		, parse<Com5>("literala").success({ { "literal", "a" } }, "")
		, parse<Com5>("literalb").success({ { "literal", "b" } }, "")
		, parse<Com5>("literald").failure()
		, parse<Com5>("aliteralaliteralcliteralbliteral").failure()
		, parse<Com5>("").success({}, "")
		;
}
TEST("Complete", "Complete<OneOrMore>")
{
	assert
		, parse<Com6>("literalaliteralcliteralcliteralb").success({ { "literal", "a" }, { "literal", "c" }, { "literal", "c" }, { "literal", "b" } }, "")
		, parse<Com6>("literalaliteralcliteralcliteralbliteral").failure()
		, parse<Com6>("literala").success({ { "literal", "a" } }, "")
		, parse<Com6>("literalb").success({ { "literal", "b" } }, "")
		, parse<Com6>("literald").failure()
		, parse<Com6>("aliteralaliteralcliteralbliteral").failure()
		, parse<Com6>("").failure()
		;
}
TEST("Complete", "Complete<ZeroOrMore>")
{
	assert
		, parse<Com7>("literalaliteralcliteralcliteralb").success({ { "literal", "a" }, { "literal", "c" }, { "literal", "c" }, { "literal", "b" } }, "")
		, parse<Com7>("literalaliteralcliteralcliteralbliteral").failure()
		, parse<Com7>("literala").success({ { "literal", "a" } }, "")
		, parse<Com7>("literalb").success({ { "literal", "b" } }, "")
		, parse<Com7>("literald").failure()
		, parse<Com7>("aliteralaliteralcliteralbliteral").failure()
		, parse<Com7>("").success({}, "")
		;
}
