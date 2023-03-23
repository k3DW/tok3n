#pragma once
#include <tok3n/parsers/repeat/Maybe.h>
#include <tok3n/parsers/repeat/OneOrMore.h>
#include <tok3n/parsers/repeat/ZeroOrMore.h>

TOK3N_BEGIN_NAMESPACE()

// ZeroOrMore
namespace detail::zeroormore
{

	template <Parser P>
	consteval auto zeroormore_oneormore(OneOrMore<P>)
	{
		return ZeroOrMore<P>{};
	}

	template <Parser P>
	consteval auto zeroormore_zeroorone(Maybe<P>)
	{
		return ZeroOrMore<P>{};
	}

}

inline namespace operators
{

template <Parser P>
requires detail::ZeroOrMore_able<P>
constexpr auto operator*(P)
{
	using namespace detail::zeroormore;

	if constexpr (IsOneOrMore<P>)       // *(+P) == *P
		return zeroormore_oneormore(P{});
	else if constexpr (IsZeroOrMore<P>) // *(*P) == *P
		return P{};
	else if constexpr (IsMaybe<P>)  // *(~P) == *P
		return zeroormore_zeroorone(P{});

	else
		return ZeroOrMore<P>{};
}

}

TOK3N_END_NAMESPACE()
