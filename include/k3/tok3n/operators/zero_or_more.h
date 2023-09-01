#pragma once
#include <k3/tok3n/parsers/repeat/Maybe.h>
#include <k3/tok3n/parsers/repeat/OneOrMore.h>
#include <k3/tok3n/parsers/repeat/ZeroOrMore.h>

namespace k3::tok3n::operators_impl {

template <Parser P>
consteval auto zero_or_more(Maybe<P>) { return ZeroOrMore<P>{}; } // *(~P) == *P

template <Parser P>
consteval auto zero_or_more(OneOrMore<P>) { return ZeroOrMore<P>{}; } // *(+P) == *P

template <Parser P>
consteval auto zero_or_more(ZeroOrMore<P>) { return ZeroOrMore<P>{}; } // *(*P) == *P

template <Parser P>
consteval auto zero_or_more(P) { return ZeroOrMore<P>{}; } // default

} // namespace k3::tok3n::operators_impl

namespace k3::tok3n {

template <Parser P>
requires ZeroOrMoreConstructible<P>
consteval auto operator*(P)
{
	return operators_impl::zero_or_more(P{});
}

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator*;

} // namespace k3::tok3n::operators

