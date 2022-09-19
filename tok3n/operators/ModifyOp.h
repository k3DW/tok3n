#pragma once
#include "parsers/_decl.h"
#include <vector>
#include <optional>

namespace k3::parser
{

template <Parser P, auto function>
constexpr auto operator%(P, fn_t<function>)
{
	return Transform<P, function>{};
}

template <Parser P>
constexpr auto operator%(P, flatten_t)
{
	if constexpr (std::same_as<std::string_view, typename P::result_type>)
		return P{};
	else
		return Flatten<P>{};
}

template <Parser P>
constexpr auto ignore(P)
{
	if constexpr (IsIgnore<P>)
		return P{};
	else
		return Ignore<P>{};
}

}
