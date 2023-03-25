#pragma once
#include <tok3n/parsers/repeat/Maybe.h>
#include <tok3n/parsers/repeat/OneOrMore.h>
#include <tok3n/parsers/repeat/ZeroOrMore.h>

TOK3N_BEGIN_NAMESPACE(detail::operators)

template <Parser P>
consteval auto zero_or_more(Maybe<P>) { return ZeroOrMore<P>{}; } // *(~P) == *P

template <Parser P>
consteval auto zero_or_more(OneOrMore<P>) { return ZeroOrMore<P>{}; } // *(+P) == *P

template <Parser P>
consteval auto zero_or_more(ZeroOrMore<P>) { return ZeroOrMore<P>{}; } // *(*P) == *P

template <Parser P>
consteval auto zero_or_more(P) { return ZeroOrMore<P>{}; } // default

TOK3N_END_NAMESPACE(detail::operators)

TOK3N_BEGIN_NAMESPACE(inline operators)

template <Parser P>
requires detail::ZeroOrMore_able<P>
consteval auto operator*(P)
{
	return detail::operators::zero_or_more(P{});
}

TOK3N_END_NAMESPACE(inline operators)
