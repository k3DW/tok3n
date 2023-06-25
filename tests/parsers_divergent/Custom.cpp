#include "pch.h"

inline void requirements()
{
	assert
		, IsParser<Cus1, CustomType, std::size_t>
		;
}

inline void parse_Transform()
{
	assert
		, parse<Cus1>("abcabcabcabc??").success(36, "")
		, parse<Cus1>("abcabcabcabc").success(12, "")
		, parse<Cus1>("abcabcabcabc ??").success(12, " ??")
		, parse<Cus1>("abc").success(3, "")
		, parse<Cus1>(" abc").failure()
		, parse<Cus1>("").failure()
		;
}
