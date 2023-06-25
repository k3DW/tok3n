#include "pch.h"

namespace k3::tok3n::tests {

inline void requirements()
{
	assert
		, IsParser<Int1, IntoType, Class1>
		, IsParser<Int2, IntoType, Class2>
		, IsParser<Int3, IntoType, Class2>
		;
}

inline void parse_Into()
{
	assert
		, parse<Int1>(" ").success(Class1(0), "")
		, parse<Int1>("a").failure()
		, parse<Int1>(".").success(Class1(1), "")
		, parse<Int1>("").failure()

		, parse<Int2>("abc.").success(Class2{ "abc", "." }, "")
		, parse<Int2>("abc . ").success(Class2{ "abc", " " }, ". ")
		, parse<Int2>("").failure()
		, parse<Int2>("abc").failure()

		, parse<Int3>("abc.").success(Class2{ "abc", "." }, "")
		, parse<Int3>("abc . ").success(Class2{ "abc", " " }, ". ")
		, parse<Int3>("").failure()
		, parse<Int3>("abc").failure()
		;
}

} // namespace k3::tok3n::tests
