// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_ALIASES_DEFAULTED_HPP
#define K3_TOK3N_DETAIL_ALIASES_DEFAULTED_HPP

#include <k3/tok3n/detail/function_objects.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/parsers/map.hpp>

namespace k3::tok3n::detail {

template <parser P, class T>
requires std::is_default_constructible_v<T>
using defaulted_parser = map_parser<P, integral_constant<default_construct_function<T>>>;

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_ALIASES_DEFAULTED_HPP
