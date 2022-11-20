#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(divergent::Into)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Int1>
		, parser_type_of<Int1>.is_Into
		, result_of<Int1>.is<Class1>

		, is_parser<Int2>
		, parser_type_of<Int2>.is_Into
		, result_of<Int2>.is<Class2>

		, is_parser<Int3>
		, parser_type_of<Int3>.is_Into
		, result_of<Int3>.is<Class2>
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
