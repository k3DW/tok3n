#include "pch.h"

TOK3N_BEGIN_NAMESPACE_TESTS(divergent::Join)

using namespace samples::all;

inline void requirements()
{
	assert
		, IsParser<Joi1, JoinType, std::string_view>
		, IsParser<Joi2, JoinType, std::string_view>
		, IsParser<Joi3, JoinType, std::string_view>
		, IsParser<Joi4, JoinType, std::string_view>
		, IsParser<Joi5, JoinType, std::string_view>
		;
}

inline void parse_Join()
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
