#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(divergent::Into)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Int1>
		, Int1::type == IntoType
		, ParserResultOf<Int1>::is<Class1>

		, is_parser<Int2>
		, Int2::type == IntoType
		, ParserResultOf<Int2>::is<Class2>

		, is_parser<Int3>
		, Int3::type == IntoType
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
