// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_OPERATORS_NOT_HPP
#define K3_TOK3N_DETAIL_OPERATORS_NOT_HPP

#include <k3/tok3n/detail/parsers/any_of.hpp>
#include <k3/tok3n/detail/parsers/none_of.hpp>

namespace k3::tok3n::detail {

namespace impl {

template <static_array arr>
constexpr auto not_operator(any_of_parser<arr>)
{
	return none_of_parser<arr>{};
}

template <static_array arr>
constexpr auto not_operator(none_of_parser<arr>)
{
	return any_of_parser<arr>{};
}

template <parser P>
constexpr auto not_operator(P) = delete;

} // namespace impl

template <parser P>
constexpr auto operator!(P)
requires requires { impl::not_operator(P{}); }
{
	return impl::not_operator(P{});
}

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_OPERATORS_NOT_HPP
