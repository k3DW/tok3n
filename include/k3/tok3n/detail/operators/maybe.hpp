// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_OPERATORS_MAYBE_HPP
#define K3_TOK3N_DETAIL_OPERATORS_MAYBE_HPP

#include <k3/tok3n/detail/parsers/maybe.hpp>
#include <k3/tok3n/detail/parsers/one_or_more.hpp>
#include <k3/tok3n/detail/parsers/zero_or_more.hpp>

namespace k3::tok3n::detail {

namespace impl {

template <parser P>
consteval auto maybe_operator(maybe_parser<P>) // ~(~P) == ~P
{
	return maybe_parser<P>{};
}

template <parser P>
consteval auto maybe_operator(one_or_more_parser<P>) // ~(+P) == *P
{
	return zero_or_more_parser<P>{};
}

template <parser P>
consteval auto maybe_operator(zero_or_more_parser<P>) // ~(*P) == *P
{
	return zero_or_more_parser<P>{};
}

template <parser P>
consteval auto maybe_operator(P) // default
{
	return maybe_parser<P>{};
}

} // namespace impl

template <parser P>
constexpr auto operator~(P)
{
	return impl::maybe_operator(P{});
}

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_OPERATORS_MAYBE_HPP