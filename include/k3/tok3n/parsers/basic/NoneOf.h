#pragma once
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <detail::static_array arr>
requires (detail::is_sorted_and_uniqued(arr.span()))
struct NoneOf : BasicBase<NoneOf<arr>>
{
	static constexpr detail::parser_family family = detail::none_of_family;
};

template <detail::static_array arr>
requires (detail::is_sorted_and_uniqued(arr.span()))
struct BasicTraits<NoneOf<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = 1;

	template <detail::equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(detail::input_span<V> input)
	{
		return input.empty() || arr.contains(input.front());
	}
};

} // namespace k3::tok3n
