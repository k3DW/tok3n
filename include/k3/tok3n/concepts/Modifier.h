#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/types/ModifierFamily.h>
#include <concepts>

namespace k3::tok3n {

template <class M>
concept Modifier =
	detail::enum_within_bounds<ModifierFamily, M::family, ModifierFamily::None, ModifierFamily::END> and
    std::derived_from<M, ModifierBase> and std::is_empty_v<M>;

} // namespace k3::tok3n
