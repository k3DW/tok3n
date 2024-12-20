// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/parsers/maybe.h>
#include <k3/tok3n/detail/parsers/one_or_more.h>
#include <k3/tok3n/detail/parsers/zero_or_more.h>

namespace k3::tok3n::detail {

namespace impl {

template <parser P>
consteval auto one_or_more_operator(maybe_parser<P>) // +(~P) == *P
{
	return zero_or_more_parser<P>{};
}

template <parser P>
consteval auto one_or_more_operator(one_or_more_parser<P>) // +(+P) == +P
{
	return one_or_more_parser<P>{};
}

template <parser P>
consteval auto one_or_more_operator(zero_or_more_parser<P>) // +(*P) == *P
{
	return zero_or_more_parser<P>{};
}

template <parser P>
consteval auto one_or_more_operator(P) // default
{
	return one_or_more_parser<P>{};
}

} // namespace impl

template <parser P>
constexpr auto operator+(P)
{
	return impl::one_or_more_operator(P{});
}

} // namespace k3::tok3n::detail
