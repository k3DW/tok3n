#include "pch.h"

inline void requirements()
{
	assert
		, IsParser<Apt1, ApplyTransformType, bool>
		, IsParser<Apt2, ApplyTransformType, std::size_t>
		;
}

inline void parse_ApplyTransform()
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
