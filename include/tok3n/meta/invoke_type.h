#pragma once
#include <tok3n/namespace.h>
#include <type_traits>

TOK3N_BEGIN_NAMESPACE(meta)

template <auto F, class... Ts>
using invoke_type = decltype(F(std::declval<Ts>()...));

TOK3N_END_NAMESPACE(meta)
