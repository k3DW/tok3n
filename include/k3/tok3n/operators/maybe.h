#pragma once
#include <k3/tok3n/parsers/repeat/Maybe.h>
#include <k3/tok3n/parsers/repeat/OneOrMore.h>
#include <k3/tok3n/parsers/repeat/ZeroOrMore.h>

TOK3N_BEGIN_NAMESPACE(detail::operators)

template <Parser P>
consteval auto maybe(Maybe<P>) { return Maybe<P>{}; } // ~(~P) == ~P

template <Parser P>
consteval auto maybe(OneOrMore<P>) { return ZeroOrMore<P>{}; } // ~(+P) == *P

template <Parser P>
consteval auto maybe(ZeroOrMore<P>) { return ZeroOrMore<P>{}; } // ~(*P) == *P

template <Parser P>
consteval auto maybe(P) { return Maybe<P>{}; } // default

TOK3N_END_NAMESPACE(detail::operators)

namespace k3::tok3n::inline operators {

template <Parser P>
requires constructible::Maybe<P>
consteval auto operator~(P)
{
	return detail::operators::maybe(P{});
}

} // namespace k3::tok3n::inline operators
