// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_EPSILON_HPP
#define K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_EPSILON_HPP

#include <k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp>

namespace k3::tok3n::detail {

template <class ValueType>
struct join_parser<epsilon_parser<ValueType>> : impl::join_parser_base<join_parser<epsilon_parser<ValueType>>>
{
    friend struct impl::join_parser_base<join_parser<epsilon_parser<ValueType>>>;
    using value_type = typename impl::join_parser_base<join_parser<epsilon_parser<ValueType>>>::value_type;

private:
    template <input_constructible_for<value_type> R, class Out>
    static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
    {
        out = Out{};
        return { success_tag, input_span{ std::forward<R>(r) } };
    }
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_EPSILON_HPP
