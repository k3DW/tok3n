#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticArray arr>
requires OneCharConstructible<arr>
struct BasicTraits<OneChar<arr>>
{
	static constexpr std::size_t length = 1;

	static constexpr bool failure_condition(Input<char> input)
	{
		return input.empty() || not arr.contains(input.front());
	}
};

template <StaticArray arr>
requires OneCharConstructible<arr>
struct OneChar : BasicBase<OneChar<arr>>
{
	static constexpr ParserType type = OneCharType;
};

} // namespace k3::tok3n
