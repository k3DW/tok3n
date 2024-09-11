#pragma once
#include <k3/tok3n/detail/functions.h>
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::aliases {

template <Parser P, class T>
using Into = Map<P, k3::tok3n::detail::integral_constant<detail::construct_function<T>>>;

} // namespace k3::tok3n::aliases
