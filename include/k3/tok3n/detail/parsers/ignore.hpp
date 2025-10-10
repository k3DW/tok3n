// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_IGNORE_HPP
#define K3_TOK3N_DETAIL_PARSERS_IGNORE_HPP

#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/result.hpp>

namespace k3::tok3n::detail {

template <parser P>
struct ignore_parser
{
    using value_type = typename P::value_type;

    template <equality_comparable_with<value_type> V>
    using result_for = std::conditional_t<std::same_as<void, V>, V, void>; // Always void

    static constexpr parser_family family = ignore_family;

    template <input_constructible_for<value_type> R>
    static constexpr auto parse(R&& r) -> result<result_for<input_value_t<R>>, input_value_t<R>>
    {
        return P::lookahead(std::forward<R>(r));
    }

    template <input_constructible_for<value_type> R>
    static constexpr auto lookahead(R&& r) -> result<void, input_value_t<R>>
    {
        return P::lookahead(std::forward<R>(r));
    }
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_PARSERS_IGNORE_HPP
