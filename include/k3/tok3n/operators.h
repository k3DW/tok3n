#pragma once

#include <k3/tok3n/detail/operators/choice.h>
#include <k3/tok3n/detail/operators/epsilon.h>
#include <k3/tok3n/operators/maybe.h>
#include <k3/tok3n/detail/operators/not.h>
#include <k3/tok3n/detail/operators/sequence.h>
#include <k3/tok3n/operators/one_or_more.h>
#include <k3/tok3n/operators/zero_or_more.h>

namespace k3::tok3n {

// This is temporary
using k3::tok3n::detail::operator|;
using k3::tok3n::detail::operator>>;

} // namespace k3::tok3n

namespace k3::tok3n {

inline constexpr detail::epsilon_operator eps = {};

} // namespace k3::tok3n
