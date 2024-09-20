#pragma once
#include <k3/tok3n/detail/parsers/basic_base.h>
#include <k3/tok3n/detail/static_array.h>

namespace k3::tok3n::detail {

template <static_array arr>
requires (is_sorted_and_uniqued(arr.span()))
struct none_of_parser : impl::basic_parser_base<none_of_parser<arr>>
{
	static constexpr parser_family family = none_of_family;
};

namespace impl {

template <static_array arr>
requires (is_sorted_and_uniqued(arr.span()))
struct basic_parser_traits<none_of_parser<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = 1;

	template <equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(input_span<V> input)
	{
		return input.empty() || arr.contains(input.front());
	}
};

} // namespace impl

} // namespace k3::tok3n::detail