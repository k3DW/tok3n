// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_ANYTHING_HPP
#define K3_TOK3N_DETAIL_PARSERS_ANYTHING_HPP

#include <k3/tok3n/detail/parsers/basic_base.hpp>

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

#endif // K3_TOK3N_DETAIL_PARSERS_ANYTHING_HPP
