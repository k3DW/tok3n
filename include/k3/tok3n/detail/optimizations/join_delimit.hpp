// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_DELIMIT_HPP
#define K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_DELIMIT_HPP

#include <k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp>

namespace k3::tok3n::detail {

template <guaranteed_contiguous P, guaranteed_contiguous D>
struct join_parser<delimit_parser<P, D>> : impl::join_parser_base<join_parser<delimit_parser<P, D>>>
{
    friend struct impl::join_parser_base<join_parser<delimit_parser<P, D>>>;
    using value_type = typename impl::join_parser_base<join_parser<delimit_parser<P, D>>>::value_type;

private:
    template <input_constructible_for<value_type> R, class Out>
    static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
    {
        input_span input{ std::forward<R>(r) };
        using V = input_value_t<R>;

        const auto* const ptr = input.data();
        std::size_t length = 0;

        result<void, V> res;
        {
            Out nested;
            res = join_parser<P>::parse_into(input, nested);
            if (not res.has_value())
                return { failure_tag, input };
            length += nested.size();
        }

        while (res.has_value())
        {
            input = res.remaining();

            Out delimit_nested;
            result<void, V> delimit_res = join_parser<P>::parse_into(input, delimit_nested);
            if (not delimit_res.has_value())
                break;

            Out nested;
            res = join_parser<P>::parse_into(input, nested);
            if (res.has_value())
                length += nested.size() + delimit_res.size();
        }

        out = Out{ ptr, length };
        return { success_tag, input };
    }
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_DELIMIT_HPP
