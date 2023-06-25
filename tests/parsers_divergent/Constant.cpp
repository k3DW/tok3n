#include "pch.h"

namespace k3::tok3n::tests {

inline void requirements()
{
	assert
		, IsParser<Con1, ConstantType, int>
		, IsParser<Con2, ConstantType, char>
		, IsParser<Con3, ConstantType, bool>
		, IsParser<Con4, ConstantType, std::nullptr_t>
		;
}

inline void parse_Constant()
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

} // namespace k3::tok3n::tests
