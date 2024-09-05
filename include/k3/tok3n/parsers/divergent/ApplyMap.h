#pragma once
#include <k3/tok3n/parsers/divergent/Map.h>
#include <k3/tok3n/detail/apply.h>

namespace k3::tok3n::aliases {

namespace detail {

template <auto function>
inline constexpr auto Apply = []<class... Args>(Args&&... args) { return k3::tok3n::detail::apply(function, std::forward<Args>(args)...); };

} // namespace detail

template <Parser P, IsConst FunctionValue>
using ApplyMap = Map<P, Const<detail::Apply<FunctionValue::value>>>;

} // namespace k3::tok3n::aliases
