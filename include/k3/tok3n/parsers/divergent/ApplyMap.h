#pragma once
#include <k3/tok3n/parsers/divergent/Map.h>
#include <k3/tok3n/detail/apply.h>

namespace k3::tok3n::aliases {

namespace detail {

template <auto function>
inline constexpr auto Apply = []<class... Args>(Args&&... args) { return k3::tok3n::detail::apply(function, std::forward<Args>(args)...); };

} // namespace detail

template <Parser P, detail::is_integral_constant FunctionValue>
using ApplyMap = Map<P, k3::tok3n::detail::integral_constant<detail::Apply<FunctionValue::value>>>;

} // namespace k3::tok3n::aliases
