#pragma once
#include "tok3n/parsers/Declarations.h"

TOK3N_BEGIN_NAMESPACE()

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
requires detail::Maybe_able<P>
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

TOK3N_END_NAMESPACE()
