#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticArray arr>
requires NoneOfConstructible<arr>
struct BasicTraits<NoneOf<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = 1;

	template <EqualityComparableWith<value_type> V>
	static constexpr bool failure_condition(Input<V> input)
	{
		return input.empty() || arr.contains(input.front());
	}
};

template <StaticArray arr>
requires NoneOfConstructible<arr>
struct NoneOf : BasicBase<NoneOf<arr>>
{
	static constexpr ParserFamily family = NoneOfFamily;
};

} // namespace k3::tok3n
