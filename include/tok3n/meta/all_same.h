#pragma once
#include <tok3n/meta/invoke_type.h>
#include <concepts>

TOK3N_BEGIN_NAMESPACE(meta)

template <class T, class... Ts>
concept all_same = (... && std::same_as<T, Ts>);

TOK3N_END_NAMESPACE(meta)
