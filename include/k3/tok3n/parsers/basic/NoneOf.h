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

	template <detail::equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(Input<V> input)
	{
		return input.empty() || arr.contains(input.front());
	}
};

template <StaticArray arr>
requires NoneOfConstructible<arr>
struct NoneOf : BasicBase<NoneOf<arr>>
{
	static constexpr detail::parser_family family = detail::none_of_family;
};

} // namespace k3::tok3n
