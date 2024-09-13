#pragma once
#include <k3/tok3n/detail/parsers/basic_parser_base.h>

namespace k3::tok3n {

template <class ValueType>
struct Anything : detail::impl::basic_parser_base<Anything<ValueType>>
{
	static constexpr detail::parser_family family = detail::anything_family;
};

namespace detail::impl {

template <class ValueType>
struct basic_parser_traits<Anything<ValueType>>
{
	using value_type = ValueType;

	static constexpr std::size_t length = 1;

	template <equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(input_span<V> input)
	{
		return input.empty();
	}
};

} // namespace detail::impl

} // namespace k3::tok3n
