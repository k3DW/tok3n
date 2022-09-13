#pragma once
#include "parsers/_decl.h"

namespace k3::parser
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