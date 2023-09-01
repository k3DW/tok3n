#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <concepts>

namespace k3::tok3n {

template <class M>
concept Modifier = std::derived_from<M, ModifierBase> and std::is_empty_v<M>;

} // namespace k3::tok3n
