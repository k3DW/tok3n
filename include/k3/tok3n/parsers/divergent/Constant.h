#pragma once
#include <k3/tok3n/detail/functions.h>
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::aliases {

template <Parser P, detail::is_integral_constant Value>
using Constant = Map<P, k3::tok3n::detail::integral_constant<detail::constant_function<Value::value>>>;

} // namespace k3::tok3n::aliases
