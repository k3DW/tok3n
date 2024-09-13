#pragma once
#include <k3/tok3n/detail/static_array.h>
#include <k3/tok3n/detail/parsers/basic_parser_base.h>

namespace k3::tok3n {

template <detail::static_array arr>
requires (detail::is_sorted_and_uniqued(arr.span()))
struct AnyOf : detail::impl::basic_parser_base<AnyOf<arr>>
{
	static constexpr detail::parser_family family = detail::any_of_family;
};

namespace detail::impl {

template <static_array arr>
requires (is_sorted_and_uniqued(arr.span()))
struct basic_parser_traits<AnyOf<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = 1;

	template <equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(input_span<V> input)
	{
		return input.empty() || not arr.contains(input.front());
	}
};

} // namespace detail::impl

} // namespace k3::tok3n
