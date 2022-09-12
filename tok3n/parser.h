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