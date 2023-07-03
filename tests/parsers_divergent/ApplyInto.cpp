#include "pch.h"

static void requirements()
{
	assert
		, IsParser<Api1, ApplyIntoType, Class2>
		, IsParser<Api2, ApplyIntoType, Class5>
		;
}

static void parse_ApplyInto()
{
	assert
		, parse<Api1>("abc.").success(Class2{ "abc", "." }, "")
		, parse<Api1>("abc . ").success(Class2{ "abc", " " }, ". ")
		, parse<Api1>("").failure()
		, parse<Api1>("abc").failure()

		, parse<Api2>(".abc").success(Class5{ ".", "abc" }, "")
		, parse<Api2>(" abc. ").success(Class5{ " ", "abc" }, ". ")
		, parse<Api2>(".").failure()
		, parse<Api2>("abc").failure()
		;
}

void ApplyInto_tests()
{
	requirements();
	parse_ApplyInto();
}
