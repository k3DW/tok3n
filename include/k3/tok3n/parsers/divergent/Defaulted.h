#pragma once
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::aliases {

namespace detail {

template <DefaultConstructible T>
inline constexpr auto DefaultConstruct = [](auto&&...) { return T{}; };

} // namespace detail

template <Parser P, DefaultConstructible T>
using Defaulted = Map<P, Const<detail::DefaultConstruct<T>>>;

} // namespace k3::tok3n::aliases
