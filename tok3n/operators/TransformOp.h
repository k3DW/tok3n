#pragma once
#include "parsers/_decl.h"

namespace k3::parser
{

template <Parser P, auto function>
constexpr auto operator%(P, fn_t<function>)
{
	return Transform<P, function>{};
}

}
