#pragma once
#include <k3/tok3n/detail/functions.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/parsers/filter.h>

namespace k3::tok3n::detail {

template <parser P, is_integral_constant FunctionValue>
using apply_filter_parser = filter_parser<P, integral_constant<apply_function<FunctionValue::value>>>;

} // namespace k3::tok3n::detail
