#pragma once
#include "tok3n/parsers/Declarations.h"

namespace k3::tok3n
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

}
