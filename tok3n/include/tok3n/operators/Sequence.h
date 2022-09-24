#pragma once
#include "tok3n/parsers/Declarations.h"

namespace k3::tok3n
{

// Literal
namespace detail::sequence
{

	template <static_string lhs, static_string rhs>
	consteval auto literal_literal(Literal<lhs>, Literal<rhs>)
	{
		return Literal<lhs + rhs>{};
	}

}

// Sequence
namespace detail::sequence
{

	template <Parser... Ps, Parser... Qs>
	consteval auto sequence_sequence(Sequence<Ps...>, Sequence<Qs...>)
	{
		return Sequence<Ps..., Qs...>{};
	}

	template <Parser... Ps, Parser P>
	consteval auto sequence_parser(Sequence<Ps...>, P)
	{
		return Sequence<Ps..., P>{};
	}

	template <Parser P, Parser... Ps>
	consteval auto parser_sequence(P, Sequence<Ps...>)
	{
		return Sequence<P, Ps...>{};
	}

}

template <Parser P1, Parser P2>
constexpr auto operator>>(P1, P2)
{
	using namespace detail::sequence;

	if constexpr (IsSequence<P1> && IsSequence<P2>) // (P1 >> P2) >> (P3 >> P4) == (P1 >> P2 >> P3 >> P4)
		return sequence_sequence(P1{}, P2{});
	else if constexpr (IsSequence<P1>)              // (P1 >> P2) >> P3 == (P1 >> P2 >> P3)
		return sequence_parser(P1{}, P2{});
	else if constexpr (IsSequence<P2>)              // P1 >> (P2 >> P3) == (P1 >> P2 >> P3)
		return parser_sequence(P1{}, P2{});

	else if constexpr (IsLiteral<P1> && IsLiteral<P2>)
		return literal_literal(P1{}, P2{});

	else
		return Sequence<P1, P2>{};
}

}
