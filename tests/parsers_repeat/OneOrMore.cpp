#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(repeat::OneOrMore)

using namespace samples::all;

void requirements()
{
	assert
		, Parser<Oom1>
		, Oom1::type == OneOrMoreType
		, ParserResultOf<Oom1>::is<std::vector<std::string_view>>

		, Parser<Oom2>
		, Oom2::type == OneOrMoreType
		, ParserResultOf<Oom2>::is<std::vector<std::string_view>>

		, Parser<Oom3>
		, Oom3::type == OneOrMoreType
		, ParserResultOf<Oom3>::is<std::vector<std::string_view>>

		, Parser<Oom4>
		, Oom4::type == OneOrMoreType
		, ParserResultOf<Oom4>::is<std::vector<std::tuple<std::string_view, std::string_view>>>
		;
}

void parse_OneOrMore_Literal()
{
	assert
		, parse<Oom1>("litera").failure()
		, parse<Oom1>("literal").success({ "literal" }, "")
		, parse<Oom1>("literally").success({ "literal" }, "ly")
		, parse<Oom1>("literallitera").success({ "literal" }, "litera")
		, parse<Oom1>("literalliterallitera").success({ "literal", "literal" }, "litera")
		, parse<Oom1>(" literalliterallitera").failure()
		, parse<Oom1>("").failure()
		;
}
void parse_OneOrMore_OneChar()
{
	assert
		, parse<Oom2>("abcdef").success({ "a", "b", "c" }, "def")
		, parse<Oom2>("fedcba").failure()
		, parse<Oom2>("cbabcccbjklmnop").success({ "c", "b", "a", "b", "c", "c", "c", "b" }, "jklmnop")
		, parse<Oom2>("").failure()
		;
}
void parse_OneOrMore_Choice()
{
	assert
		, parse<Oom3>("abliteralcbliteralcf").success({ "a", "b", "literal", "c", "b", "literal", "c" }, "f")
		, parse<Oom3>("abliteralcblitralcf").success({ "a", "b", "literal", "c", "b" }, "litralcf")
		, parse<Oom3>("literalabacliteral").success({ "literal", "a", "b", "a", "c", "literal" }, "")
		, parse<Oom3>("").failure()
		;
}
void parse_OneOrMore_Sequence()
{
	assert
		, parse<Oom4>("literalaliteralcliteralcliteralb").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "")
		, parse<Oom4>("literalaliteralcliteralcliteralbliteral").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "literal")
		, parse<Oom4>("aliteralaliteralcliteralbliteral").failure()
		, parse<Oom4>("").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(repeat::OneOrMore)
#endif
