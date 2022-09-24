#pragma once
#include "tok3n/parsers/Declarations.h"

BEGIN_NAMESPACE_TOK3N()

// Maybe
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

	if constexpr (IsMaybe<P>)       // ~(~P) == ~P
		return P{};
	else if constexpr (IsOneOrMore<P>)  // ~(+P) == *P
		return zeroorone_oneormore(P{});
	else if constexpr (IsZeroOrMore<P>) // ~(*P) == *P
		return P{};

	else
		return Maybe<P>{};
}

END_NAMESPACE_TOK3N()
