#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(divergent::ApplyInto)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Api1>
		, Api1::type == ParserType::ApplyInto
		, ParserResultOf<Api1>::is<Class2>

		, is_parser<Api2>
		, Api2::type == ParserType::ApplyInto
		, ParserResultOf<Api2>::is<Class5>
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
