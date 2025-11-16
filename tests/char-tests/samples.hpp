// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_CHAR_TESTS_SAMPLES_HPP
#define K3_TOK3N_TESTS_CHAR_TESTS_SAMPLES_HPP

#include "common.hpp"

#if defined(VALUE_TYPE_CHAR)

    #if defined(VALUE_TYPE_WCHAR_T)
    #error Can only define one VALUE_TYPE_XYZ macro.
    #endif

    #define TT(x) x
    using value_type = char;

#elif defined(VALUE_TYPE_WCHAR_T)

    #if defined(VALUE_TYPE_CHAR)
    #error Can only define one VALUE_TYPE_XYZ macro.
    #endif

    #define TT(x) L ## x
    using value_type = wchar_t;

#else
#error Must define exactly one VALUE_TYPE_XYZ macro.
#endif

#include "samples/helpers.hpp"

#include "samples/basic-char.hpp"
#include "samples/sub_parsers.hpp"

#include "samples/classes.hpp"
#include "samples/functions.hpp"

#include "samples/adaptor.hpp"
#include "samples/compound.hpp"
#include "samples/divergent.hpp"
#include "samples/repeat.hpp"

namespace k3::tok3n::tests {

using namespace ::k3::tok3n::detail;

template <class... Ts>
requires true
inline constexpr auto samples_list<Ts...> =
    adaptor_samples +
    basic_samples +
    compound_samples +
    divergent_samples +
    repeat_samples;

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_CHAR_TESTS_SAMPLES_HPP
