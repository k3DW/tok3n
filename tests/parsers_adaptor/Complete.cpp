#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Complete)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Com1>
		, parser_type_of<Com1>.is_Complete
		, ParserResultOf<Com1>::is<std::string_view>

		, is_parser<Com2>
		, parser_type_of<Com2>.is_Complete
		, ParserResultOf<Com2>::is<std::string_view>

		, is_parser<Com3>
		, parser_type_of<Com3>.is_Complete
		, ParserResultOf<Com3>::is<std::string_view>

		, is_parser<Com4>
		, parser_type_of<Com4>.is_Complete
		, ParserResultOf<Com4>::is<std::tuple<std::string_view, std::string_view>>

		, is_parser<Com5>
		, parser_type_of<Com5>.is_Complete
		, ParserResultOf<Com5>::is<std::optional<std::tuple<std::string_view, std::string_view>>>
		;
}

void parse_Complete_Literal()
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
void parse_Complete_OneChar()
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
void parse_Complete_Choice()
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
void parse_Complete_Sequence()
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
void parse_Complete_Maybe()
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
void parse_Complete_OneOrMore()
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
void parse_Complete_ZeroOrMore()
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

TOK3N_END_NAMESPACE_TESTS(adaptor::Complete)
#endif
