#pragma once
#include <tok3n/utilities/namespace.h>

TOK3N_BEGIN_NAMESPACE()

template <class T>
concept ImplicitlyDefaultConstructible = requires (void(fn)(T)) { fn({}); };

TOK3N_END_NAMESPACE()
