#pragma once
#include <tok3n/utilities/namespace.h>

TOK3N_BEGIN_NAMESPACE()

template <class T>
concept implicitly_default_constructible = requires (void(fn)(T)) { fn({}); };

TOK3N_END_NAMESPACE()
