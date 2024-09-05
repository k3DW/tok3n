#pragma once
#include <k3/tok3n/parsers/divergent/ApplyMap.h>
#include <k3/tok3n/parsers/divergent/Into.h>

namespace k3::tok3n::aliases {

template <Parser P, class T>
using ApplyInto = Map<P, Const<detail::Apply<detail::Construct<T>>>>;

} // namespace k3::tok3n::aliases
