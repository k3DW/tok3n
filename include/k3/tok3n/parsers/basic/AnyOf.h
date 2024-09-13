#pragma once
#include <k3/tok3n/detail/static_array.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <detail::static_array arr>
requires (detail::is_sorted_and_uniqued(arr.span()))
struct AnyOf : BasicBase<AnyOf<arr>>
{
	static constexpr detail::parser_family family = detail::any_of_family;
};

template <detail::static_array arr>
requires (detail::is_sorted_and_uniqued(arr.span()))
struct BasicTraits<AnyOf<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = 1;

	template <detail::equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(detail::input_span<V> input)
	{
		return input.empty() || not arr.contains(input.front());
	}
};

} // namespace k3::tok3n
