#pragma once
#include <tok3n/parsers/repeat/Maybe.h>
#include <tok3n/parsers/repeat/OneOrMore.h>
#include <tok3n/parsers/repeat/ZeroOrMore.h>

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

inline namespace operators
{

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

}

TOK3N_END_NAMESPACE()
