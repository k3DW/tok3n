#pragma once
#include <k3/tok3n/detail/parsers/basic_parser_base.h>

namespace k3::tok3n {

template <detail::static_array arr>
requires (detail::is_sorted_and_uniqued(arr.span()))
struct NoneOf : detail::impl::basic_parser_base<NoneOf<arr>>
{
	static constexpr detail::parser_family family = detail::none_of_family;
};

namespace detail::impl {

template <static_array arr>
requires (is_sorted_and_uniqued(arr.span()))
struct basic_parser_traits<NoneOf<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = 1;

	template <equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(input_span<V> input)
	{
		return input.empty() || arr.contains(input.front());
	}
};

} // namespace detail::impl

} // namespace k3::tok3n
