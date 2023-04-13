#pragma once
#include <k3/tok3n/parsers/basic/Literal.h>
#include <k3/tok3n/parsers/compound/Sequence.h>

TOK3N_BEGIN_NAMESPACE(detail::operators)

template <StaticString lhs, StaticString rhs>
consteval auto sequence(Literal<lhs>, Literal<rhs>) { return Literal<lhs + rhs>{}; } // "ab" >> "cd" == "abcd"

template <Parser... P1s, Parser... P2s>
consteval auto sequence(Sequence<P1s...>, Sequence<P2s...>) { return Sequence<P1s..., P2s...>{}; } // (P1 >> P2) >> (P3 >> P4) == (P1 >> P2 >> P3 >> P4)

template <Parser... P1s, Parser P2>
consteval auto sequence(Sequence<P1s...>, P2) { return Sequence<P1s..., P2>{}; } // (P1 >> P2) >> P3 == (P1 >> P2 >> P3)

template <Parser P1, Parser... P2s>
consteval auto sequence(P1, Sequence<P2s...>) { return Sequence<P1, P2s...>{}; } // P1 >> (P2 >> P3) == (P1 >> P2 >> P3)

template <Parser P1, Parser P2>
consteval auto sequence(P1, P2) { return Sequence<P1, P2>{}; } // default

TOK3N_END_NAMESPACE(detail::operators)

TOK3N_BEGIN_NAMESPACE(inline operators)

template <Parser P1, Parser P2>
consteval auto operator>>(P1, P2)
{
	return detail::operators::sequence(P1{}, P2{});
}

TOK3N_END_NAMESPACE(inline operators)
