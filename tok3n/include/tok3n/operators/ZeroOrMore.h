#pragma once
#include "tok3n/parsers/Declarations.h"

namespace k3::tok3n
{

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

}
