#pragma once
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::aliases {

namespace detail {

template <auto value>
inline constexpr auto Constant = [](auto&&...) { return value; };

} // namespace detail

template <Parser P, IsConst Value>
using Constant = Map<P, k3::tok3n::detail::integral_constant<detail::Constant<Value::value>>>;

} // namespace k3::tok3n::aliases
