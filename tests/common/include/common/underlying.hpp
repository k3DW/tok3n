// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_UNDERLYING_HPP
#define K3_TOK3N_TESTS_COMMON_UNDERLYING_HPP

#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/static_array.hpp>

template <template <auto> class ParserTemplate, k3::tok3n::detail::static_array arr>
consteval auto underlying_impl(ParserTemplate<arr>)
{
	return arr;
}

template <template <class> class ParserTemplate, k3::tok3n::detail::parser P>
consteval auto underlying_impl(ParserTemplate<P>)
{
	return P{};
}

template <k3::tok3n::detail::parser P>
inline constexpr auto underlying_v = underlying_impl(P{});

template <k3::tok3n::detail::parser P>
using underlying_t = decltype(underlying_impl(P{}));

#endif // K3_TOK3N_TESTS_COMMON_UNDERLYING_HPP
