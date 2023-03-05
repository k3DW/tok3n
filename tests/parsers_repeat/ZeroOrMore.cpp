#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(repeat::ZeroOrMore)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Zom1>
		, parser_type_of<Zom1>.is_ZeroOrMore
		, result_of<Zom1>.is<std::vector<std::string_view>>

		, is_parser<Zom2>
		, parser_type_of<Zom2>.is_ZeroOrMore
		, result_of<Zom2>.is<std::vector<std::string_view>>

		, is_parser<Zom3>
		, parser_type_of<Zom3>.is_ZeroOrMore
		, result_of<Zom3>.is<std::vector<std::string_view>>

		, is_parser<Zom4>
		, parser_type_of<Zom4>.is_ZeroOrMore
		, result_of<Zom4>.is<std::vector<std::tuple<std::string_view, std::string_view>>>
		;
}

void parse_ZeroOrMore_Literal()
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
void parse_ZeroOrMore_OneChar()
{
	assert
		, parse<Zom2>("abcdef").success({ "a", "b", "c" }, "def")
		, parse<Zom2>("fedcba").success({}, "fedcba")
		, parse<Zom2>("cbabcccbjklmnop").success({ "c", "b", "a", "b", "c", "c", "c", "b" }, "jklmnop")
		, parse<Zom2>("").success({}, "")
		;
}
void parse_ZeroOrMore_Choice()
{
	assert
		, parse<Zom3>("abliteralcbliteralcf").success({ "a", "b", "literal", "c", "b", "literal", "c" }, "f")
		, parse<Zom3>("abliteralcblitralcf").success({ "a", "b", "literal", "c", "b" }, "litralcf")
		, parse<Zom3>("literalabacliteral").success({ "literal", "a", "b", "a", "c", "literal" }, "")
		, parse<Zom3>("").success({}, "")
		;
}
void parse_ZeroOrMore_Sequence()
{
	assert
		, parse<Zom4>("literalaliteralcliteralcliteralb").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "")
		, parse<Zom4>("literalaliteralcliteralcliteralbliteral").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "literal")
		, parse<Zom4>("aliteralaliteralcliteralbliteral").success({}, "aliteralaliteralcliteralbliteral")
		, parse<Zom4>("").success({}, "")
		;
}

TOK3N_END_NAMESPACE_TESTS(repeat::ZeroOrMore)
#endif
