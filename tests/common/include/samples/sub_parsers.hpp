// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_SAMPLES_SUB_PARSERS_HPP
#define K3_TOK3N_TESTS_SAMPLES_SUB_PARSERS_HPP

#include "samples.hpp"

using _11 = All1;
using _12 = Any1;
using _13 = k3::tok3n::detail::choice_parser<All1, Any1>;
using _14 = k3::tok3n::detail::sequence_parser<All1, Any1>;

using _21 = ABC;
using _22 = k3::tok3n::detail::one_or_more_parser<ABC>;
using _23 = k3::tok3n::detail::maybe_parser<k3::tok3n::detail::choice_parser<ABC, QQ>>;
using _24 = k3::tok3n::detail::sequence_parser<ABC, k3::tok3n::detail::zero_or_more_parser<QQ>>;
using _25 = k3::tok3n::detail::sequence_parser<k3::tok3n::detail::one_or_more_parser<ABC>, k3::tok3n::detail::maybe_parser<k3::tok3n::detail::choice_parser<ABC, QQ>>>;

#endif // K3_TOK3N_TESTS_SAMPLES_SUB_PARSERS_HPP
