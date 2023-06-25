#include "pch.h"

inline void requirements()
{
	assert
		, IsParser<Ign1, IgnoreType, void>
		, IsParser<Ign2, IgnoreType, void>
		, IsParser<Ign3, IgnoreType, void>
		, IsParser<Ign4, IgnoreType, void>
		, IsParser<Ign5, IgnoreType, void>
		;
}

inline void parse_Ignore()
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
