#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(divergent::ApplyInto)

using namespace samples::all;

void requirements()
{
	assert
		, IsParser<Api1, ApplyIntoType, Class2>
		, IsParser<Api2, ApplyIntoType, Class5>
		;
}

void parse_ApplyInto()
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

TOK3N_END_NAMESPACE_TESTS(divergent::ApplyInto)
#endif
