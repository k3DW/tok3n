#pragma once
#include <k3/tok3n/parsers/basic/fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticString str>
requires OneCharConstructible<str>
struct BasicTraits<OneChar<str>>
{
	static constexpr std::size_t length = 1;

	static constexpr bool failure_condition(Input input)
	{
		return input.empty() || not str.contains(input.front());
	}
};

template <StaticString str>
requires OneCharConstructible<str>
struct OneChar : BasicBase<OneChar<str>>
{
	static constexpr ParserType type = OneCharType;
};

} // namespace k3::tok3n
