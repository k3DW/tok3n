#pragma once
#include <k3/tok3n/namespace.h>
#include <type_traits>

namespace k3::tok3n::meta {

template <auto F, class... Ts>
using invoke_type = decltype(F(std::declval<Ts>()...));

} // namespace k3::tok3n::meta
