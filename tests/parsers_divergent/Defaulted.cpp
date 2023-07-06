#include "pch.h"

TEST("Defaulted", "Requirements")
{
	assert
		, IsParser<Def1, DefaultedType, int>
		, IsParser<Def2, DefaultedType, Class3>
		;
}

TEST("Defaulted", "Parse all")
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
