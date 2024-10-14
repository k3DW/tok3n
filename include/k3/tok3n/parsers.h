// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once

#include <k3/tok3n/detail/aliases/apply_filter.h>
#include <k3/tok3n/detail/aliases/apply_into.h>
#include <k3/tok3n/detail/aliases/apply_map.h>
#include <k3/tok3n/detail/aliases/constant.h>
#include <k3/tok3n/detail/aliases/defaulted.h>
#include <k3/tok3n/detail/aliases/into.h>

#include <k3/tok3n/detail/optimizations/join_exactly_basic.h>
#include <k3/tok3n/detail/optimizations/join_maybe_basic.h>
#include <k3/tok3n/detail/optimizations/join_one_or_more_basic.h>
#include <k3/tok3n/detail/optimizations/join_zero_or_more_basic.h>

#include <k3/tok3n/detail/parsers/all_of.h>
#include <k3/tok3n/detail/parsers/any_of.h>
#include <k3/tok3n/detail/parsers/anything.h>
#include <k3/tok3n/detail/parsers/choice.h>
#include <k3/tok3n/detail/parsers/complete.h>
#include <k3/tok3n/detail/parsers/custom.h>
#include <k3/tok3n/detail/parsers/delimit.h>
#include <k3/tok3n/detail/parsers/epsilon.h>
#include <k3/tok3n/detail/parsers/exactly.h>
#include <k3/tok3n/detail/parsers/filter.h>
#include <k3/tok3n/detail/parsers/ignore.h>
#include <k3/tok3n/detail/parsers/join.h>
#include <k3/tok3n/detail/parsers/map.h>
#include <k3/tok3n/detail/parsers/maybe.h>
#include <k3/tok3n/detail/parsers/named.h>
#include <k3/tok3n/detail/parsers/none_of.h>
#include <k3/tok3n/detail/parsers/one_or_more.h>
#include <k3/tok3n/detail/parsers/sequence.h>
#include <k3/tok3n/detail/parsers/zero_or_more.h>

namespace k3::tok3n {

using ::k3::tok3n::detail::custom_parser;

} // namespace k3::tok3n
