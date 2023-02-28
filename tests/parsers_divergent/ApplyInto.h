#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(divergent::ApplyInto)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Api1>
		, parser_type_of<Api1>.is_ApplyInto
		, result_of<Api1>.is<Class2>

		, is_parser<Api2>
		, parser_type_of<Api2>.is_ApplyInto
		, result_of<Api2>.is<Class5>
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
