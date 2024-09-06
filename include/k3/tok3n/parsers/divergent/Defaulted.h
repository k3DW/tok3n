#pragma once
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::aliases {

namespace detail {

template <class T>
requires std::is_default_constructible_v<T>
inline constexpr auto DefaultConstruct = [](auto&&...) { return T{}; };

} // namespace detail

template <Parser P, class T>
requires std::is_default_constructible_v<T>
using Defaulted = Map<P, Const<detail::DefaultConstruct<T>>>;

} // namespace k3::tok3n::aliases
