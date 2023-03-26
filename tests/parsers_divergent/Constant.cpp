#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(divergent::Constant)

using namespace samples::all;

void requirements()
{
	assert
		, Parser<Con1>
		, Con1::type == ConstantType
		, ParserResultOf<Con1>::is<int>

		, Parser<Con2>
		, Con2::type == ConstantType
		, ParserResultOf<Con2>::is<char>
		
		, Parser<Con3>
		, Con3::type == ConstantType
		, ParserResultOf<Con3>::is<bool>
		
		, Parser<Con4>
		, Con4::type == ConstantType
		, ParserResultOf<Con4>::is<std::nullptr_t>
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
