// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_MODIFIER_HPP
#define K3_TOK3N_DETAIL_MODIFIER_HPP

#include <k3/tok3n/detail/type_traits.hpp>

namespace k3::tok3n::detail {

struct modifier_base {};

template <class M>
concept modifier =
    std::derived_from<M, modifier_base> and
    std::is_empty_v<M>;

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_MODIFIER_HPP
