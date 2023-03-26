#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(divergent::Join)

using namespace samples::all;

void requirements()
{
	assert
		, Parser<Joi1>
		, Joi1::type == JoinType
		, ParserResultOf<Joi1>::is<std::string_view>
		
		, Parser<Joi2>
		, Joi2::type == JoinType
		, ParserResultOf<Joi2>::is<std::string_view>
		
		, Parser<Joi3>
		, Joi3::type == JoinType
		, ParserResultOf<Joi3>::is<std::string_view>
		
		, Parser<Joi4>
		, Joi4::type == JoinType
		, ParserResultOf<Joi4>::is<std::string_view>
		
		, Parser<Joi5>
		, Joi5::type == JoinType
		, ParserResultOf<Joi5>::is<std::string_view>
		;
}

void parse_Join()
{
	assert
		, parse<Joi1>("abcabc").success("abc", "abc")
		, parse<Joi1>("Abcabc").failure()
		, parse<Joi1>(" abcabc").failure()

		, parse<Joi2>("abcabcabcab").success("abcabcabc", "ab")
		, parse<Joi2>("").failure()
		, parse<Joi2>("ab").failure()
		, parse<Joi2>("abc").success("abc", "")

		, parse<Joi3>("abcabc").success("abc", "abc")
		, parse<Joi3>("a??bcabc").success("", "a??bcabc")
		, parse<Joi3>("").success("", "")
		, parse<Joi3>("??abcabc").success("??", "abcabc")
		, parse<Joi3>(" ??abcabc").success("", " ??abcabc")

		, parse<Joi4>("abc???????").success("abc??????", "?")
		, parse<Joi4>("??abc???????").failure()
		, parse<Joi4>("abc??abc???????").success("abc??", "abc???????")
		, parse<Joi4>("abc ??abc???????").success("abc", " ??abc???????")
		, parse<Joi4>("").failure()

		, parse<Joi5>("abcabcabcabc??").success("abcabcabcabc??", "")
		, parse<Joi5>("abcabcabcabc").success("abcabcabcabc", "")
		, parse<Joi5>("abcabcabcabc ??").success("abcabcabcabc", " ??")
		, parse<Joi5>("abc").success("abc", "")
		, parse<Joi5>(" abc").failure()
		, parse<Joi5>("").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(divergent::Join)
#endif
