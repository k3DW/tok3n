#pragma once
#include <k3/tok3n/namespace.h>

namespace k3::tok3n {

template <class T>
concept implicitly_default_constructible = requires (void(fn)(T)) { fn({}); };

} // namespace k3::tok3n
