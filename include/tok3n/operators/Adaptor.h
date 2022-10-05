#pragma once
#include "tok3n/parsers/Declarations.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P, auto function>
constexpr auto operator%(P, fn_t<function>)
{
	return Transform<P, function>{};
}

template <Parser P>
constexpr auto operator%(P, join_t)
{
	if constexpr (std::same_as<Input, typename P::result_type>)
		return P{};
	else
		return Join<P>{};
}

template <Parser P>
constexpr auto ignore(P)
{
	if constexpr (IsIgnore<P>)
		return P{};
	else
		return Ignore<P>{};
}

template <Parser P, Parser Delimiter>
constexpr auto delimit(P, Delimiter)
{
	return Delimit<P, Delimiter>{};
}

TOK3N_END_NAMESPACE()
