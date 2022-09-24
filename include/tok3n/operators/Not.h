#pragma once
#include "tok3n/parsers/Declarations.h"

BEGIN_NAMESPACE_TOK3N()

template <static_string str>
constexpr auto operator!(OneChar<str>)
{
	return NotChar<str>{};
}
template <static_string str>
constexpr auto operator!(NotChar<str>)
{
	return OneChar<str>{};
}

END_NAMESPACE_TOK3N()
