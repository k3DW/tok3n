// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_MAYBE_HPP
#define K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_MAYBE_HPP

#include <k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp>

namespace k3::tok3n::detail {

template <guaranteed_contiguous P>
struct join_parser<maybe_parser<P>> : impl::join_parser_base<join_parser<maybe_parser<P>>>
{
    friend struct impl::join_parser_base<join_parser<maybe_parser<P>>>;
    using value_type = typename impl::join_parser_base<join_parser<maybe_parser<P>>>::value_type;

private:
    template <input_constructible_for<value_type> R, class Out>
    static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
    {
        const input_span input{ std::forward<R>(r) };
        using V = input_value_t<R>;

        result<void, V> res = join_parser<P>::parse(input, out);
        return { success_tag, res.remaining() };
    }
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_MAYBE_HPP
