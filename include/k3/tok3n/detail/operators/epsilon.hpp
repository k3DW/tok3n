// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_OPERATORS_EPSILON_HPP
#define K3_TOK3N_DETAIL_OPERATORS_EPSILON_HPP

#include <k3/tok3n/detail/operators/choice.hpp>
#include <k3/tok3n/detail/parsers/epsilon.hpp>

namespace k3::tok3n::detail {

struct epsilon_operator
{
	template <class V>
	static constexpr epsilon_parser<V> of = {};
};

template <parser P>
constexpr auto operator|(P, epsilon_operator)
{
	return impl::choice_operator(P{}, epsilon_parser<typename P::value_type>{});
}

template <parser P>
constexpr auto operator|(epsilon_operator, P) = delete;

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_OPERATORS_EPSILON_HPP
