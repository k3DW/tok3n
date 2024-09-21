#pragma once
#include <k3/tok3n/detail/parsers/any_of.h>
#include <k3/tok3n/detail/parsers/none_of.h>

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
