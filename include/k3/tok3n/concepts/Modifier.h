#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/types/ModifierFamily.h>
#include <concepts>

namespace k3::tok3n {

template <class M>
concept Modifier =
	requires { typename std::integral_constant<ModifierFamily, M::family>; } &&
	static_cast<int>(M::family) > static_cast<int>(ModifierFamily::None) &&
	static_cast<int>(M::family) < static_cast<int>(ModifierFamily::END) &&
    std::derived_from<M, ModifierBase> and std::is_empty_v<M>;

} // namespace k3::tok3n
