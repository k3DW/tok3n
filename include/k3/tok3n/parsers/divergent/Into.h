#pragma once
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::aliases {

namespace detail {

template <class T>
inline constexpr auto Construct = []<class... Args>(Args&&... args) { return T(std::forward<Args>(args)...); };

} // namespace detail

template <Parser P, class T>
using Into = Map<P, Const<detail::Construct<T>>>;

} // namespace k3::tok3n::aliases
