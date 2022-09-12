#pragma once
#include <algorithm>
#include <array>
#include <iterator>
#include <optional>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "util/static_string.h"

#include "parsers/parsers.h"
#include "operators/ChoiceOp.h"

namespace k3::parser
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



	// OneOrMore
	namespace detail::oneormore
	{

		template <Parser P>
		consteval auto oneormore_zeroorone(ZeroOrOne<P>)
		{
			return ZeroOrMore<P>{};
		}

	}



	// ZeroOrMore
	namespace detail::zeroormore
	{

		template <Parser P>
		consteval auto zeroormore_oneormore(OneOrMore<P>)
		{
			return ZeroOrMore<P>{};
		}

		template <Parser P>
		consteval auto zeroormore_zeroorone(ZeroOrOne<P>)
		{
			return ZeroOrMore<P>{};
		}

	}



	// ZeroOrOne
	namespace detail::zeroorone
	{

		template <Parser P>
		consteval auto zeroorone_oneormore(OneOrMore<P>)
		{
			return ZeroOrMore<P>{};
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

	template <Parser P>
	constexpr auto operator+(P)
	{
		using namespace detail::oneormore;

		if constexpr (IsOneOrMore<P>)       // +(+P) == +P
			return P{};
		else if constexpr (IsZeroOrMore<P>) // +(*P) == *P
			return P{};
		else if constexpr (IsZeroOrOne<P>)  // +(~P) == *P
			return oneormore_zeroorone(P{});

		else
			return OneOrMore<P>{};
	}

	template <Parser P>
	constexpr auto operator*(P)
	{
		using namespace detail::zeroormore;

		if constexpr (IsOneOrMore<P>)       // *(+P) == *P
			return zeroormore_oneormore(P{});
		else if constexpr (IsZeroOrMore<P>) // *(*P) == *P
			return P{};
		else if constexpr (IsZeroOrOne<P>)  // *(~P) == *P
			return zeroormore_zeroorone(P{});

		else
			return ZeroOrMore<P>{};
	}

	template <Parser P>
	constexpr auto operator~(P)
	{
		using namespace detail::zeroorone;

		if constexpr (IsZeroOrOne<P>)       // ~(~P) == ~P
			return P{};
		else if constexpr (IsOneOrMore<P>)  // ~(+P) == *P
			return zeroorone_oneormore(P{});
		else if constexpr (IsZeroOrMore<P>) // ~(*P) == *P
			return P{};

		else
			return ZeroOrOne<P>{};
	}

	template <static_string str>
	constexpr auto operator!(OneChar<str>)
	{
		return NotChar<str>{};
	}
	template <static_string str>
	constexpr auto operator!(NotChar<str>)
	{
		return OneChar<str>{};
	}










}