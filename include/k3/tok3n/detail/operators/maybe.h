#pragma once
#include <k3/tok3n/parsers/repeat/Maybe.h>
#include <k3/tok3n/parsers/repeat/OneOrMore.h>
#include <k3/tok3n/parsers/repeat/ZeroOrMore.h>

namespace k3::tok3n::detail {

namespace impl {

template <parser P>
consteval auto maybe_operator(Maybe<P>) // ~(~P) == ~P
{
	return Maybe<P>{};
}

template <parser P>
consteval auto maybe_operator(OneOrMore<P>) // ~(+P) == *P
{
	return ZeroOrMore<P>{};
}

template <parser P>
consteval auto maybe_operator(ZeroOrMore<P>) // ~(*P) == *P
{
	return ZeroOrMore<P>{};
}

template <parser P>
consteval auto maybe_operator(P) // default
{
	return Maybe<P>{};
}

} // namespace impl

template <parser P>
constexpr auto operator~(P)
{
	return impl::maybe_operator(P{});
}

} // namespace k3::tok3n::detail
