// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_ALIASES_APPLY_FILTER_HPP
#define K3_TOK3N_DETAIL_ALIASES_APPLY_FILTER_HPP

#include <k3/tok3n/detail/function_objects.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/parsers/filter.hpp>

namespace k3::tok3n::detail {

template <parser P, is_integral_constant FunctionValue>
using apply_filter_parser = filter_parser<P, integral_constant<apply_function<FunctionValue::value>>>;

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_ALIASES_APPLY_FILTER_HPP
