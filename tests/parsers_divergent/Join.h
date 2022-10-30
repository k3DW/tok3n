#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(divergent::Join)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Joi1>
		, parser_type_of<Joi1>.is_Join
		, result_of<Joi1>.is<std::string_view>
		
		, is_parser<Joi2>
		, parser_type_of<Joi2>.is_Join
		, result_of<Joi2>.is<std::string_view>
		
		, is_parser<Joi3>
		, parser_type_of<Joi3>.is_Join
		, result_of<Joi3>.is<std::string_view>
		
		, is_parser<Joi4>
		, parser_type_of<Joi4>.is_Join
		, result_of<Joi4>.is<std::string_view>
		
		, is_parser<Joi5>
		, parser_type_of<Joi5>.is_Join
		, result_of<Joi5>.is<std::string_view>
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
