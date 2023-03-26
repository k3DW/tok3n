#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Transform)

using namespace samples::all;

void requirements()
{
	assert
		, IsParser<Tra1, TransformType, std::size_t>
		, IsParser<Tra2, TransformType, std::vector<char>>
		, IsParser<Tra3, TransformType, bool>
		, IsParser<Tra4, TransformType, std::size_t>
		;
}

void parse_Transform()
{
	assert
		, parse<Tra1>("abcabcabcab").success(3, "ab")
		, parse<Tra1>("").failure()
		, parse<Tra1>("ab").failure()
		, parse<Tra1>("abc").success(1, "")
		
		, parse<Tra2>("abcabc").success({ 'a', 'b', 'c' }, "abc")
		, parse<Tra2>("a??bcabc").success({}, "a??bcabc")
		, parse<Tra2>("").success({}, "")
		, parse<Tra2>("??abcabc").success({ '?', '?' }, "abcabc")
		, parse<Tra2>(" ??abcabc").success({}, " ??abcabc")
		
		, parse<Tra3>("abc???????").success(false, "?")
		, parse<Tra3>("??abc???????").failure()
		, parse<Tra3>("abc??abc???????").success(false, "abc???????")
		, parse<Tra3>("abc ??abc???????").success(true, " ??abc???????")
		, parse<Tra3>("").failure()
		
		, parse<Tra4>("abcabcabcabc??").success(36, "")
		, parse<Tra4>("abcabcabcabc").success(12, "")
		, parse<Tra4>("abcabcabcabc ??").success(12, " ??")
		, parse<Tra4>("abc").success(3, "")
		, parse<Tra4>(" abc").failure()
		, parse<Tra4>("").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(adaptor::Transform)
#endif
