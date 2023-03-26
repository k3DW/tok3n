#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Ignore)

using namespace samples::all;

void requirements()
{
	assert
		, Parser<Ign1>
		, Ign1::type == IgnoreType
		, ParserResultOf<Ign1>::is<void>

		, Parser<Ign2>
		, Ign2::type == IgnoreType
		, ParserResultOf<Ign2>::is<void>

		, Parser<Ign3>
		, Ign3::type == IgnoreType
		, ParserResultOf<Ign3>::is<void>

		, Parser<Ign4>
		, Ign4::type == IgnoreType
		, ParserResultOf<Ign4>::is<void>

		, Parser<Ign5>
		, Ign5::type == IgnoreType
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
