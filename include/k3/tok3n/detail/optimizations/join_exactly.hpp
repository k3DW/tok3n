// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_EXACTLY_HPP
#define K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_EXACTLY_HPP

#include <k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp>

namespace k3::tok3n::detail {

template <guaranteed_contiguous P, integral_constant_of<std::size_t> N>
struct join_parser<exactly_parser<P, N>> : impl::join_parser_base<join_parser<exactly_parser<P, N>>>
{
    friend struct impl::join_parser_base<join_parser<exactly_parser<P, N>>>;
    using value_type = typename impl::join_parser_base<join_parser<exactly_parser<P, N>>>::value_type;

private:
    template <input_constructible_for<value_type> R, class Out>
    static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
    {
        input_span input{ std::forward<R>(r) };
        using V = input_value_t<R>;

        const input_span original_input = input;
        const auto* const ptr = input.data();
        std::size_t length = 0;

        for (std::size_t i = 0; i != N::value; ++i)
        {
            Out nested;
            result<void, V> res = join_parser<P>::parse_into(input, nested);
            if (not res.has_value())
                return { failure, original_input };
            input = res.remaining();
            length += nested.size();
        }

        out = Out{ ptr, length };
        return { success, input };
    }
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_EXACTLY_HPP
