#pragma once
#include <tok3n/parsers/basic/Literal.h>
#include <tok3n/parsers/compound/Sequence.h>

TOK3N_BEGIN_NAMESPACE()

namespace detail::Sequence_operator
{

	template <StaticString lhs, StaticString rhs>
	consteval auto Literal_and_Literal(Literal<lhs>, Literal<rhs>)
	{
		return Literal<lhs + rhs>{};
	}

	template <Parser... Ps, Parser... Qs>
	consteval auto Sequence_and_Sequence(Sequence<Ps...>, Sequence<Qs...>)
	{
		return Sequence<Ps..., Qs...>{};
	}

	template <Parser... Ps, Parser P>
	consteval auto Sequence_and_anything(Sequence<Ps...>, P)
	{
		return Sequence<Ps..., P>{};
	}

	template <Parser P, Parser... Ps>
	consteval auto anything_and_Sequence(P, Sequence<Ps...>)
	{
		return Sequence<P, Ps...>{};
	}

}

inline namespace operators
{

template <Parser P1, Parser P2>
constexpr auto operator>>(P1, P2)
{
	using namespace detail::Sequence_operator;

	if constexpr (IsLiteral<P1> && IsLiteral<P2>) // "ab" >> "cd" == "abcd"
		return Literal_and_Literal(P1{}, P2{});

	else if constexpr (IsSequence<P1> && IsSequence<P2>) // (P1 >> P2) >> (P3 >> P4) == (P1 >> P2 >> P3 >> P4)
		return Sequence_and_Sequence(P1{}, P2{});
	else if constexpr (IsSequence<P1>)                   // (P1 >> P2) >> P3 == (P1 >> P2 >> P3)
		return Sequence_and_anything(P1{}, P2{});
	else if constexpr (IsSequence<P2>)                   // P1 >> (P2 >> P3) == (P1 >> P2 >> P3)
		return anything_and_Sequence(P1{}, P2{});

	else
		return Sequence<P1, P2>{};
}

}

TOK3N_END_NAMESPACE()
