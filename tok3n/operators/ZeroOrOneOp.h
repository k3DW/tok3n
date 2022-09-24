#pragma once
#include "parsers/_decl.h"

namespace k3::tok3n
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

}
