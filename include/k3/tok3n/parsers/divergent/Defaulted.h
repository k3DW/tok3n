#pragma once
#include <k3/tok3n/detail/functions.h>
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::aliases {

template <k3::tok3n::detail::parser P, class T>
requires std::is_default_constructible_v<T>
using Defaulted = Map<P, k3::tok3n::detail::integral_constant<detail::default_construct_function<T>>>;

} // namespace k3::tok3n::aliases
