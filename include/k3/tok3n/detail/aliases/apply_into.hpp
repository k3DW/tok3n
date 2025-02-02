// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_ALIASES_APPLY_INTO_HPP
#define K3_TOK3N_DETAIL_ALIASES_APPLY_INTO_HPP

#include <k3/tok3n/detail/functions.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/parsers/map.hpp>

namespace k3::tok3n::detail {

template <parser P, class T>
using apply_into_parser = map_parser<P, integral_constant<apply_function<construct_function<T>>>>;

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_ALIASES_APPLY_INTO_HPP
