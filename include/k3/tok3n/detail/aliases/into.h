// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/functions.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/parsers/map.h>

namespace k3::tok3n::detail {

template <parser P, class T>
using into_parser = map_parser<P, integral_constant<construct_function<T>>>;

} // namespace k3::tok3n::detail
