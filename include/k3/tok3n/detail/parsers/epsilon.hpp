// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_EPSILON_HPP
#define K3_TOK3N_DETAIL_PARSERS_EPSILON_HPP

#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/result.hpp>

namespace k3::tok3n::detail {

template <class ValueType>
struct epsilon_parser
{
	using value_type = ValueType;
	
	template <equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<std::same_as<void, V>, V, void>; // Always void

	static constexpr parser_family family = epsilon_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		const input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;
        return result<void, V>{ success_tag, input };
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		const input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;
        return result<void, V>{ success_tag, input };
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_PARSERS_EPSILON_HPP
