#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(divergent::Defaulted)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Def1>
		, Def1::type == ParserType::Defaulted
		, ParserResultOf<Def1>::is<int>

		, is_parser<Def2>
		, Def2::type == ParserType::Defaulted
		, ParserResultOf<Def2>::is<Class3>
		;
}

void parse_Join()
{
	assert
		, parse<Def1>("abcabcabcab").success(0, "ab")
		, parse<Def1>("").failure()
		, parse<Def1>("ab").failure()
		, parse<Def1>("abc").success(0, "")

		, parse<Def2>("abcabc").success(Class3{}, "abc")
		, parse<Def2>("a??bcabc").success(Class3{}, "a??bcabc")
		, parse<Def2>("").success(Class3{}, "")
		, parse<Def2>("??abcabc").success(Class3{}, "abcabc")
		, parse<Def2>(" ??abcabc").success(Class3{}, " ??abcabc")
		;
}

TOK3N_END_NAMESPACE_TESTS(divergent::Defaulted)
#endif
