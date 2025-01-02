// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/parsers/basic_base.hpp>
#include <k3/tok3n/detail/static_array.hpp>

namespace k3::tok3n::detail {

template <static_array arr>
requires (is_sorted_and_uniqued(arr.span()))
struct any_of_parser : impl::basic_parser_base<any_of_parser<arr>>
{
	static constexpr parser_family family = any_of_family;
};

namespace impl {

template <static_array arr>
requires (is_sorted_and_uniqued(arr.span()))
struct basic_parser_traits<any_of_parser<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = 1;

	template <equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(input_span<V> input)
	{
		return input.empty() || not arr.contains(input.front());
	}
};

} // namespace impl

} // namespace k3::tok3n::detail
