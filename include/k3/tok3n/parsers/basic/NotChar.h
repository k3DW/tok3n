#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticArray arr>
requires NotCharConstructible<arr>
struct BasicTraits<NotChar<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = 1;

	static constexpr bool failure_condition(Input<value_type> input)
	{
		return input.empty() || arr.contains(input.front());
	}
};

template <StaticArray arr>
requires NotCharConstructible<arr>
struct NotChar : BasicBase<NotChar<arr>>
{
	static constexpr ParserType type = NotCharType;
};

} // namespace k3::tok3n
