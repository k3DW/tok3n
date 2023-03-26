#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(divergent::Into)

using namespace samples::all;

void requirements()
{
	assert
		, IsParser<Int1, IntoType>
		, ParserResultOf<Int1>::is<Class1>

		, IsParser<Int2, IntoType>
		, ParserResultOf<Int2>::is<Class2>

		, IsParser<Int3, IntoType>
		, ParserResultOf<Int3>::is<Class2>
		;
}

void parse_Into()
{
	assert
		, parse<Int1>(" ").success(Class1(0), "")
		, parse<Int1>("a").failure()
		, parse<Int1>(".").success(Class1(1), "")
		, parse<Int1>("").failure()

		, parse<Int2>("abc.").success(Class2{ "abc", "." }, "")
		, parse<Int2>("abc . ").success(Class2{ "abc", " " }, ". ")
		, parse<Int2>("").failure()
		, parse<Int2>("abc").failure()

		, parse<Int3>("abc.").success(Class2{ "abc", "." }, "")
		, parse<Int3>("abc . ").success(Class2{ "abc", " " }, ". ")
		, parse<Int3>("").failure()
		, parse<Int3>("abc").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(divergent::Into)
#endif
