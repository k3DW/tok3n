#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Ignore)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Ign1>
		, parser_type_of<Ign1>.is_Ignore
		, ParserResultOf<Ign1>::is<void>

		, is_parser<Ign2>
		, parser_type_of<Ign2>.is_Ignore
		, ParserResultOf<Ign2>::is<void>

		, is_parser<Ign3>
		, parser_type_of<Ign3>.is_Ignore
		, ParserResultOf<Ign3>::is<void>

		, is_parser<Ign4>
		, parser_type_of<Ign4>.is_Ignore
		, ParserResultOf<Ign4>::is<void>

		, is_parser<Ign5>
		, parser_type_of<Ign5>.is_Ignore
		, ParserResultOf<Ign5>::is<void>
		;
}

void parse_Ignore()
{
	assert
		, parse<Ign1>("abcabc").success("abc")
		, parse<Ign1>("Abcabc").failure()
		, parse<Ign1>(" abcabc").failure()

		, parse<Ign2>("abcabcabcab").success("ab")
		, parse<Ign2>("").failure()
		, parse<Ign2>("ab").failure()
		, parse<Ign2>("abc").success("")

		, parse<Ign3>("abcabc").success("abc")
		, parse<Ign3>("a??bcabc").success("a??bcabc")
		, parse<Ign3>("").success("")
		, parse<Ign3>("??abcabc").success("abcabc")
		, parse<Ign3>(" ??abcabc").success(" ??abcabc")

		, parse<Ign4>("abc???????").success("?")
		, parse<Ign4>("??abc???????").failure()
		, parse<Ign4>("abc??abc???????").success("abc???????")
		, parse<Ign4>("abc ??abc???????").success(" ??abc???????")
		, parse<Ign4>("").failure()

		, parse<Ign5>("abcabcabcabc??").success("")
		, parse<Ign5>("abcabcabcabc").success("")
		, parse<Ign5>("abcabcabcabc ??").success(" ??")
		, parse<Ign5>("abc").success("")
		, parse<Ign5>(" abc").failure()
		, parse<Ign5>("").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(adaptor::Ignore)
#endif
