#pragma once
#include <k3/tok3n/detail/parsers/basic_parser_base.h>

namespace k3::tok3n {

template <detail::static_array arr>
struct AllOf : detail::impl::basic_parser_base<AllOf<arr>>
{
	static constexpr detail::parser_family family = detail::all_of_family;
};

namespace detail::impl {

template <static_array arr>
struct basic_parser_traits<AllOf<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = arr.size();

	template <equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(input_span<V> input)
	{
		return (input.size() < length) || (input_span<value_type>(arr.span()) != input_span<V>(input.first(length)));
	}
};

} // namespace detail::impl

} // namespace k3::tok3n
