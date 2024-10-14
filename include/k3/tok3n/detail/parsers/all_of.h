// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/parsers/basic_base.h>
#include <k3/tok3n/detail/static_array.h>

namespace k3::tok3n::detail {

template <static_array arr>
struct all_of_parser : impl::basic_parser_base<all_of_parser<arr>>
{
	static constexpr parser_family family = all_of_family;
};

namespace impl {

template <static_array arr>
struct basic_parser_traits<all_of_parser<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = arr.size();

	template <equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(input_span<V> input)
	{
		return (input.size() < length) || (input_span<value_type>(arr.span()) != input_span<V>(input.first(length)));
	}
};

} // namespace impl

} // namespace k3::tok3n::detail
