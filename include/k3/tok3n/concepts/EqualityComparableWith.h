#pragma once
#include <concepts>

namespace k3::tok3n {

// std::equality_comparable_with requires a common reference
template <class T, class U>
concept EqualityComparableWith = requires (T t, U u) { { t == u } -> std::convertible_to<bool>; };

} // namespace k3::tok3n
