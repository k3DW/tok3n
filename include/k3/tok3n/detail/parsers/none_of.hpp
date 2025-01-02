// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_NONE_OF_HPP
#define K3_TOK3N_DETAIL_PARSERS_NONE_OF_HPP

#include <k3/tok3n/detail/parsers/basic_base.hpp>
#include <k3/tok3n/detail/static_array.hpp>

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

#endif // K3_TOK3N_DETAIL_PARSERS_NONE_OF_HPP
