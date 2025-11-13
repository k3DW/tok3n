// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_SAMPLES_BASIC_CHAR_HPP
#define K3_TOK3N_TESTS_SAMPLES_BASIC_CHAR_HPP

#include "samples.hpp"
#include "common/samples_list.hpp"

using Any1 = k3::tok3n::detail::any_of_parser<TT("abc")>; constexpr Any1 any1;
using Any2 = k3::tok3n::detail::any_of_parser<TT("bcd")>; constexpr Any2 any2;
using Any3 = k3::tok3n::detail::any_of_parser<TT("xyz")>; constexpr Any3 any3;
using Any4 = k3::tok3n::detail::any_of_parser<TT("cd")>;  constexpr Any4 any4;

using Non1 = k3::tok3n::detail::none_of_parser<TT("abc")>; constexpr Non1 none1;
using Non2 = k3::tok3n::detail::none_of_parser<TT("bcd")>; constexpr Non2 none2;
using Non3 = k3::tok3n::detail::none_of_parser<TT("xyz")>; constexpr Non3 none3;
using Non4 = k3::tok3n::detail::none_of_parser<TT("cd")>;  constexpr Non4 none4;
using Non5 = k3::tok3n::detail::none_of_parser<TT("z")>;   constexpr Non5 none5;

using All1 = k3::tok3n::detail::all_of_parser<TT("literal")>; constexpr All1 all1;
using All2 = k3::tok3n::detail::all_of_parser<TT("ly")>;      constexpr All2 all2;
using All3 = k3::tok3n::detail::all_of_parser<TT("test")>;    constexpr All3 all3;
using All4 = k3::tok3n::detail::all_of_parser<TT("ab")>;      constexpr All4 all4;

using Eps1 = k3::tok3n::detail::epsilon_parser<::value_type>;  constexpr Eps1 eps1;
using Ant1 = k3::tok3n::detail::anything_parser<::value_type>; constexpr Ant1 ant1;

using QQ       = k3::tok3n::detail::all_of_parser<TT("??")>;  constexpr QQ       qq;
using ABC      = k3::tok3n::detail::all_of_parser<TT("abc")>; constexpr ABC      abc;
using Comma    = k3::tok3n::detail::any_of_parser<TT(",")>;   constexpr Comma    comma;
using SpaceDot = k3::tok3n::detail::any_of_parser<TT(" .")>;  constexpr SpaceDot spacedot;

inline constexpr auto basic_samples = k3::tok3n::tests::parser_list_t<
    Any1, Any2, Any3, Any4,
    Non1, Non2, Non3, Non4, Non5,
    All1, All2, All3, All4,
    Eps1, Ant1,
    QQ, ABC, Comma, SpaceDot
>{};

#endif // K3_TOK3N_TESTS_SAMPLES_BASIC_CHAR_HPP
