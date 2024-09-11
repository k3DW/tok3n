#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticArray arr>
struct BasicTraits<AllOf<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = arr.size();

	template <detail::equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(Input<V> input)
	{
		return (input.size() < length) || (Input<value_type>(arr.span()) != Input<V>(input.first(length)));
	}
};

template <StaticArray arr>
struct AllOf : BasicBase<AllOf<arr>>
{
	static constexpr detail::parser_family family = detail::all_of_family;
};

} // namespace k3::tok3n
