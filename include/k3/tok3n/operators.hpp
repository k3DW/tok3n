// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once

#include <k3/tok3n/detail/operators/choice.hpp>
#include <k3/tok3n/detail/operators/epsilon.hpp>
#include <k3/tok3n/detail/operators/maybe.hpp>
#include <k3/tok3n/detail/operators/modifier.hpp>
#include <k3/tok3n/detail/operators/not.hpp>
#include <k3/tok3n/detail/operators/sequence.hpp>
#include <k3/tok3n/detail/operators/one_or_more.hpp>
#include <k3/tok3n/detail/operators/zero_or_more.hpp>

namespace k3::tok3n {

inline constexpr detail::epsilon_operator eps = {};

} // namespace k3::tok3n
