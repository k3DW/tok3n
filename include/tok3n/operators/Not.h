#pragma once
#include "tok3n/parsers/Declarations.h"

TOK3N_BEGIN_NAMESPACE()

inline namespace operators
{

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

}

TOK3N_END_NAMESPACE()
