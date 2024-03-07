#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticArray arr>
requires AnyOfConstructible<arr>
struct BasicTraits<AnyOf<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = 1;

	template <std::convertible_to<value_type> V>
	static constexpr bool failure_condition(Input<V> input)
	{
		return input.empty() || not arr.contains(input.front());
	}
};

template <StaticArray arr>
requires AnyOfConstructible<arr>
struct AnyOf : BasicBase<AnyOf<arr>>
{
	static constexpr ParserFamily family = AnyOfFamily;
};

} // namespace k3::tok3n
