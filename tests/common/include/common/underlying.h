#pragma once
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/static_array.h>

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
