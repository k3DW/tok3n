#include "pch.h"

TOK3N_BEGIN_NAMESPACE(tests)

inline void requirements()
{
	assert
		, IsParser<Oom1, OneOrMoreType, std::vector<std::string_view>>
		, IsParser<Oom2, OneOrMoreType, std::vector<std::string_view>>
		, IsParser<Oom3, OneOrMoreType, std::vector<std::string_view>>
		, IsParser<Oom4, OneOrMoreType, std::vector<std::tuple<std::string_view, std::string_view>>>
		;
}

inline void parse_OneOrMore_Literal()
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
inline void parse_OneOrMore_OneChar()
{
	assert
		, parse<Oom2>("abcdef").success({ "a", "b", "c" }, "def")
		, parse<Oom2>("fedcba").failure()
		, parse<Oom2>("cbabcccbjklmnop").success({ "c", "b", "a", "b", "c", "c", "c", "b" }, "jklmnop")
		, parse<Oom2>("").failure()
		;
}
inline void parse_OneOrMore_Choice()
{
	assert
		, parse<Oom3>("abliteralcbliteralcf").success({ "a", "b", "literal", "c", "b", "literal", "c" }, "f")
		, parse<Oom3>("abliteralcblitralcf").success({ "a", "b", "literal", "c", "b" }, "litralcf")
		, parse<Oom3>("literalabacliteral").success({ "literal", "a", "b", "a", "c", "literal" }, "")
		, parse<Oom3>("").failure()
		;
}
inline void parse_OneOrMore_Sequence()
{
	assert
		, parse<Oom4>("literalaliteralcliteralcliteralb").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "")
		, parse<Oom4>("literalaliteralcliteralcliteralbliteral").success({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "literal")
		, parse<Oom4>("aliteralaliteralcliteralbliteral").failure()
		, parse<Oom4>("").failure()
		;
}

TOK3N_END_NAMESPACE(tests)
