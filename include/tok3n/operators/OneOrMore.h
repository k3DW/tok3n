#pragma once
#include <tok3n/parsers/repeat/Maybe.h>
#include <tok3n/parsers/repeat/OneOrMore.h>
#include <tok3n/parsers/repeat/ZeroOrMore.h>

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

inline namespace operators
{

template <Parser P>
requires detail::OneOrMore_able<P>
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

}

TOK3N_END_NAMESPACE()
