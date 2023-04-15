#pragma once
#include <k3/tok3n/namespace.h>
#include <k3/tok3n/types/ModifierBase.h>
#include <concepts>

TOK3N_BEGIN_NAMESPACE()

template <class M>
concept Modifier = std::derived_from<M, ModifierBase> and std::is_empty_v<M>;

TOK3N_END_NAMESPACE()
