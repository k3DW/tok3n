#pragma once
#include "tok3n/parsers/Declarations.h"

TOK3N_BEGIN_NAMESPACE()

// OneOrMore
namespace detail::oneormore
{

	template <Parser P>
	consteval auto oneormore_zeroorone(Maybe<P>)
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
	else if constexpr (IsMaybe<P>)  // +(~P) == *P
		return oneormore_zeroorone(P{});

	else
		return OneOrMore<P>{};
}

TOK3N_END_NAMESPACE()
