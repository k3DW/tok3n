#pragma once
#include "tok3n/parsers/Declarations.h"

TOK3N_BEGIN_NAMESPACE()



template <auto function> struct fn_t final {};
template <auto function> constexpr auto fn = fn_t<function>{};

template <Parser P, auto function>
constexpr auto operator%(P, fn_t<function>)
{
	return Transform<P, function>{};
}



constexpr struct join_t final {} join;

template <Parser P>
constexpr auto operator%(P, join_t)
{
	if constexpr (std::same_as<Input, typename P::result_type>)
		return P{};
	else
		return Join<P>{};
}



template <class T> struct into_t final {};
template <class T> constexpr auto into = into_t<T>{};

template <Parser P, class T>
constexpr auto operator%(P, into_t<T>)
{
	return Into<P, T>{};
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
