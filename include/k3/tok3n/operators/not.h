#pragma once
#include <k3/tok3n/parsers/basic/OneChar.h>
#include <k3/tok3n/parsers/basic/NotChar.h>

TOK3N_BEGIN_NAMESPACE(inline operators)

template <StaticString str>
consteval auto operator!(OneChar<str>)
{
	return NotChar<str>{};
}

template <StaticString str>
consteval auto operator!(NotChar<str>)
{
	return OneChar<str>{};
}

template <Parser P>
consteval auto operator!(P) = delete;

TOK3N_END_NAMESPACE(inline operators)
