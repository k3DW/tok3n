#pragma once

#include <k3/tok3n/detail/operators/choice.h>
#include <k3/tok3n/detail/operators/epsilon.h>
#include <k3/tok3n/detail/operators/maybe.h>
#include <k3/tok3n/detail/operators/modifier.h>
#include <k3/tok3n/detail/operators/not.h>
#include <k3/tok3n/detail/operators/sequence.h>
#include <k3/tok3n/detail/operators/one_or_more.h>
#include <k3/tok3n/detail/operators/zero_or_more.h>

namespace k3::tok3n {

inline constexpr detail::epsilon_operator eps = {};

} // namespace k3::tok3n
