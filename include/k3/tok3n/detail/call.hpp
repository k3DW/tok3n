// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_CALL_HPP
#define K3_TOK3N_DETAIL_CALL_HPP

#include <k3/tok3n/detail/parser.hpp>

namespace k3::tok3n::detail {

enum class call_kind
{
    parse,
    parse_into,
    lookahead,
};

struct call_parse_t
{
    static constexpr call_kind kind = call_kind::parse;
    template <parser P, class R>
    constexpr auto operator()(P, R&& r) const
    {
        return P::parse(std::forward<R>(r));
    }
};
inline constexpr call_parse_t call_parse{};

struct call_parse_into_t
{
    static constexpr call_kind kind = call_kind::parse_into;
    template <parser P, class R, class Out>
    constexpr auto operator()(P, R&& r, Out& out) const
    {
        return P::parse(std::forward<R>(r), out);
    }
};
inline constexpr call_parse_into_t call_parse_into{};

struct call_lookahead_t
{
    static constexpr call_kind kind = call_kind::lookahead;
    template <parser P, class R>
    constexpr auto operator()(P, R&& r) const
    {
        return P::lookahead(std::forward<R>(r));
    }
};
inline constexpr call_lookahead_t call_lookahead{};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_CALL_HPP
