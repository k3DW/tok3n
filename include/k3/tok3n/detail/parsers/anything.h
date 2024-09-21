#pragma once
#include <k3/tok3n/detail/parsers/basic_base.h>

namespace k3::tok3n::detail {

template <class ValueType>
struct anything_parser : impl::basic_parser_base<anything_parser<ValueType>>
{
	static constexpr parser_family family = anything_family;
};

namespace impl {

template <class ValueType>
struct basic_parser_traits<anything_parser<ValueType>>
{
	using value_type = ValueType;

	static constexpr std::size_t length = 1;

	template <equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(input_span<V> input)
	{
		return input.empty();
	}
};

} // namespace impl

} // namespace k3::tok3n::detail
