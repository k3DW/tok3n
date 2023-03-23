#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(divergent::Constant)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Con1>
		, parser_type_of<Con1>.is_Constant
		, result_of<Con1>.is<int>

		, is_parser<Con2>
		, parser_type_of<Con2>.is_Constant
		, result_of<Con2>.is<char>
		
		, is_parser<Con3>
		, parser_type_of<Con3>.is_Constant
		, result_of<Con3>.is<bool>
		
		, is_parser<Con4>
		, parser_type_of<Con4>.is_Constant
		, result_of<Con4>.is<std::nullptr_t>
		;
}

void parse_Constant()
{
	assert
		, parse<Con1>("abcabcabcab").success(1, "ab")
		, parse<Con1>("").failure()
		, parse<Con1>("ab").failure()
		, parse<Con1>("abc").success(1, "")
		
		, parse<Con2>("abcabc").success('t', "abc")
		, parse<Con2>("a??bcabc").success('t', "a??bcabc")
		, parse<Con2>("").success('t', "")
		, parse<Con2>("??abcabc").success('t', "abcabc")
		, parse<Con2>(" ??abcabc").success('t', " ??abcabc")
		
		, parse<Con3>("abc???????").success(true, "?")
		, parse<Con3>("??abc???????").failure()
		, parse<Con3>("abc??abc???????").success(true, "abc???????")
		, parse<Con3>("abc ??abc???????").success(true, " ??abc???????")
		, parse<Con3>("").failure()
		
		, parse<Con4>("abcabcabcabc??").success(nullptr, "")
		, parse<Con4>("abcabcabcabc").success(nullptr, "")
		, parse<Con4>("abcabcabcabc ??").success(nullptr, " ??")
		, parse<Con4>("abc").success(nullptr, "")
		, parse<Con4>(" abc").failure()
		, parse<Con4>("").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(divergent::Constant)
#endif