#pragma once
#include <k3/tok3n/parsers/repeat/Maybe.h>
#include <k3/tok3n/parsers/repeat/OneOrMore.h>
#include <k3/tok3n/parsers/repeat/ZeroOrMore.h>

namespace k3::tok3n::operators_impl {

template <Parser P>
consteval auto maybe(Maybe<P>) { return Maybe<P>{}; } // ~(~P) == ~P

template <Parser P>
consteval auto maybe(OneOrMore<P>) { return ZeroOrMore<P>{}; } // ~(+P) == *P

template <Parser P>
consteval auto maybe(ZeroOrMore<P>) { return ZeroOrMore<P>{}; } // ~(*P) == *P

template <Parser P>
consteval auto maybe(P) { return Maybe<P>{}; } // default

} // namespace k3::tok3n::operators_impl

namespace k3::tok3n {

template <Parser P>
constexpr auto operator~(P)
{
	return operators_impl::maybe(P{});
}

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator~;

} // namespace k3::tok3n::operators
