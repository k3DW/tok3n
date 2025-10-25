// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_HPP
#define K3_TOK3N_TESTS_COMMON_HPP

#include "framework.hpp"

#include "common/asserts/Concept.hpp"
#include "common/asserts/Operation.hpp"
#include "common/asserts/Parse.hpp"

#include "common/fragments/fails_parsing.hpp"
#include "common/fragments/has_family.hpp"
#include "common/fragments/has_value_type.hpp"
#include "common/fragments/is_not_parser_for.hpp"
#include "common/fragments/is_parser_for.hpp"
#include "common/fragments/modifier_value.hpp"
#include "common/fragments/parser_family.hpp"
#include "common/fragments/parser_fragment_builder.hpp"
#include "common/fragments/parser_value.hpp"
#include "common/fragments/succeeds_parsing.hpp"

#include "common/underlying.hpp"
#include "common/wrappers.hpp"

#include <k3/tok3n.hpp>

#include <map>
#include <memory>
#include <numeric>
#include <string>
#include <string_view>
#include <source_location>
#include <unordered_map>
#include <vector>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

#endif // K3_TOK3N_TESTS_COMMON_HPP
