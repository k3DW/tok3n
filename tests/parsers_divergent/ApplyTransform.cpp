#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::ApplyTransform)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Apt1>
		, parser_type_of<Apt1>.is_ApplyTransform
		, ParserResultOf<Apt1>::is<bool>

		, is_parser<Apt2>
		, parser_type_of<Apt2>.is_ApplyTransform
		, ParserResultOf<Apt2>::is<std::size_t>
		;
}

void parse_ApplyTransform()
{
	assert
		, parse<Apt1>("abc???????").success(false, "?")
		, parse<Apt1>("??abc???????").failure()
		, parse<Apt1>("abc??abc???????").success(false, "abc???????")
		, parse<Apt1>("abc ??abc???????").success(true, " ??abc???????")
		, parse<Apt1>("").failure()

		, parse<Apt2>("abcabcabcabc??").success(36, "")
		, parse<Apt2>("abcabcabcabc").success(12, "")
		, parse<Apt2>("abcabcabcabc ??").success(12, " ??")
		, parse<Apt2>("abc").success(3, "")
		, parse<Apt2>(" abc").failure()
		, parse<Apt2>("").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(adaptor::ApplyTransform)
#endif
