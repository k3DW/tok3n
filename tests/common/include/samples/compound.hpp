// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_SAMPLES_COMPOUND_HPP
#define K3_TOK3N_TESTS_SAMPLES_COMPOUND_HPP

#include "samples.hpp"

using Cho1 = k3::tok3n::detail::choice_parser<All4, Non4>;       constexpr Cho1 cho1;
using Cho2 = k3::tok3n::detail::choice_parser<Non4, All4>;       constexpr Cho2 cho2;
using Cho3 = k3::tok3n::detail::choice_parser<All4, Any4, Non5>; constexpr Cho3 cho3;
using Cho4 = k3::tok3n::detail::choice_parser<Non5, All4, Any4>; constexpr Cho4 cho4;
using Cho5 = k3::tok3n::detail::choice_parser<Ign1, Ign2>;       constexpr Cho5 cho5;

using Seq1 = k3::tok3n::detail::sequence_parser<All4, Non4>;       constexpr Seq1 seq1;
using Seq2 = k3::tok3n::detail::sequence_parser<Non4, All4>;       constexpr Seq2 seq2;
using Seq3 = k3::tok3n::detail::sequence_parser<All4, Any4, Non5>; constexpr Seq3 seq3;
using Seq4 = k3::tok3n::detail::sequence_parser<Non5, All4, Any4>; constexpr Seq4 seq4;
using Seq5 = k3::tok3n::detail::sequence_parser<Ign1, Ign2>;       constexpr Seq5 seq5;

#define COMPOUND_SAMPLES               \
    (Cho1) (Cho2) (Cho3) (Cho4) (Cho5) \
    (Seq1) (Seq2) (Seq3) (Seq4) (Seq5)

#endif // K3_TOK3N_TESTS_SAMPLES_COMPOUND_HPP
