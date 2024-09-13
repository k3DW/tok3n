#pragma once
#include <k3/tok3n/parsers/basic/AnyOf.h>
#include <k3/tok3n/parsers/basic/NoneOf.h>

namespace k3::tok3n::detail {

namespace impl {

template <static_array arr>
constexpr auto not_operator(AnyOf<arr>)
{
	return NoneOf<arr>{};
}

template <static_array arr>
constexpr auto not_operator(NoneOf<arr>)
{
	return AnyOf<arr>{};
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
