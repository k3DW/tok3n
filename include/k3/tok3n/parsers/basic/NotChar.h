#pragma once
#include <k3/tok3n/parsers/basic/fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticString str>
requires NotCharConstructible<str>
struct BasicTraits<NotChar<str>>
{
	static constexpr std::size_t length = 1;

	static constexpr bool failure_condition(Input input)
	{
		return input.empty() || str.contains(input.front());
	}
};

template <StaticString str>
requires NotCharConstructible<str>
struct NotChar : BasicBase<NotChar<str>>
{
	static constexpr ParserType type = NotCharType;
};

} // namespace k3::tok3n
