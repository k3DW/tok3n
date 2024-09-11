#pragma once
#include <k3/tok3n/detail/functions.h>
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::aliases {

template <Parser P, detail::is_integral_constant FunctionValue>
using ApplyMap = Map<P, k3::tok3n::detail::integral_constant<detail::apply_function<FunctionValue::value>>>;

} // namespace k3::tok3n::aliases
