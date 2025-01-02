// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/functions.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/parsers/map.hpp>

namespace k3::tok3n::detail {

template <parser P, is_integral_constant FunctionValue>
using apply_map_parser = map_parser<P, integral_constant<apply_function<FunctionValue::value>>>;

} // namespace k3::tok3n::detail
