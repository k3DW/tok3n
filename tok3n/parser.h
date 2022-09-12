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
#include "operators/operators.h"

namespace k3::parser
{




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