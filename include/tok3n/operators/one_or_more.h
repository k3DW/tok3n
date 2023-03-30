#pragma once
#include <tok3n/parsers/repeat/Maybe.h>
#include <tok3n/parsers/repeat/OneOrMore.h>
#include <tok3n/parsers/repeat/ZeroOrMore.h>

TOK3N_BEGIN_NAMESPACE(detail::operators)

template <Parser P>
consteval auto one_or_more(Maybe<P>) { return ZeroOrMore<P>{}; } // +(~P) == *P

template <Parser P>
consteval auto one_or_more(OneOrMore<P>) { return OneOrMore<P>{}; } // +(+P) == +P

template <Parser P>
consteval auto one_or_more(ZeroOrMore<P>) { return ZeroOrMore<P>{}; } // +(*P) == *P

template <Parser P>
consteval auto one_or_more(P) { return OneOrMore<P>{}; } // default

TOK3N_END_NAMESPACE(detail::operators)

TOK3N_BEGIN_NAMESPACE(inline operators)

template <Parser P>
requires constructible::OneOrMore<P>
consteval auto operator+(P)
{
	return detail::operators::one_or_more(P{});
}

TOK3N_END_NAMESPACE(inline operators)
