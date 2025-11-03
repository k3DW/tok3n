// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_SAMPLES_ADAPTOR_HPP
#define K3_TOK3N_TESTS_SAMPLES_ADAPTOR_HPP

#include "samples.hpp"
#include "common/samples_list.hpp"

using Ign1 = k3::tok3n::detail::ignore_parser<_21>; constexpr Ign1 ign1;
using Ign2 = k3::tok3n::detail::ignore_parser<_22>; constexpr Ign2 ign2;
using Ign3 = k3::tok3n::detail::ignore_parser<_23>; constexpr Ign3 ign3;
using Ign4 = k3::tok3n::detail::ignore_parser<_24>; constexpr Ign4 ign4;
using Ign5 = k3::tok3n::detail::ignore_parser<_25>; constexpr Ign5 ign5;

using Com1 = k3::tok3n::detail::complete_parser<_11>;                        constexpr Com1 com1;
using Com2 = k3::tok3n::detail::complete_parser<_12>;                        constexpr Com2 com2;
using Com3 = k3::tok3n::detail::complete_parser<_13>;                        constexpr Com3 com3;
using Com4 = k3::tok3n::detail::complete_parser<_14>;                        constexpr Com4 com4;
using Com5 = k3::tok3n::detail::complete_parser<k3::tok3n::detail::maybe_parser<_14>>;      constexpr Com5 com5;
using Com6 = k3::tok3n::detail::complete_parser<k3::tok3n::detail::one_or_more_parser<_14>>;  constexpr Com6 com6;
using Com7 = k3::tok3n::detail::complete_parser<k3::tok3n::detail::zero_or_more_parser<_14>>; constexpr Com7 com7;

using Nam1 = k3::tok3n::detail::named_parser<_21, "nam1">; constexpr Nam1 nam1;
using Nam2 = k3::tok3n::detail::named_parser<_22, "nam2">; constexpr Nam2 nam2;
using Nam3 = k3::tok3n::detail::named_parser<_23, "nam3">; constexpr Nam3 nam3;
using Nam4 = k3::tok3n::detail::named_parser<_24, "nam4">; constexpr Nam4 nam4;

#define ADAPTOR_SAMPLES                              \
    (Ign1) (Ign2) (Ign3) (Ign4) (Ign5)               \
    (Com1) (Com2) (Com3) (Com4) (Com5) (Com6) (Com7) \
    (Nam1) (Nam2) (Nam3) (Nam4)

inline constexpr auto adaptor_samples = k3::tok3n::tests::parser_list_t<
    Ign1, Ign2, Ign3, Ign4, Ign5,
    Com1, Com2, Com3, Com4, Com5, Com6, Com7,
    Nam1, Nam2, Nam3, Nam4
>{};

#endif // K3_TOK3N_TESTS_SAMPLES_ADAPTOR_HPP
