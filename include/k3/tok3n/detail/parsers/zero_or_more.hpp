// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_ZERO_OR_MORE_HPP
#define K3_TOK3N_DETAIL_PARSERS_ZERO_OR_MORE_HPP

#include <k3/tok3n/detail/call.hpp>
#include <k3/tok3n/detail/cpo.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/result.hpp>
#include <vector>

namespace k3::tok3n::detail {

template <parser P>
struct zero_or_more_parser
{
    using value_type = typename P::value_type;

    template <equality_comparable_with<value_type> V>
    using result_for = std::conditional_t<
        std::same_as<void, typename P::template result_for<V>>,
        void,
        std::vector<typename P::template result_for<V>>
    >;

    static constexpr parser_family family = zero_or_more_family;

    template <input_constructible_for<value_type> R>
    static constexpr auto parse(R&& r) -> result<result_for<input_value_t<R>>, input_value_t<R>>
    {
        if constexpr (std::same_as<void, result_for<input_value_t<R>>>)
        {
            return _impl(call_parse, std::forward<R>(r));
        }
        else
        {
            result_for<input_value_t<R>> out;
            return _impl(call_parse_into, std::forward<R>(r), out)
                .with_value(std::move(out));
        }
    }

    template <input_constructible_for<value_type> R, class Out>
    requires parsable_into<P, R&&, typename P::template result_for<input_value_t<R>>>
        and pushable<Out, typename P::template result_for<input_value_t<R>>&&>
    static constexpr auto parse(R&& r, Out& out) -> result<void, input_value_t<R>>
    {
        return _impl(call_parse_into, std::forward<R>(r), out);
    }

    template <input_constructible_for<value_type> R>
    static constexpr auto lookahead(R&& r) -> result<void, input_value_t<R>>
    {
        return _impl(call_lookahead, std::forward<R>(r));
    }

private:
    template <class Call, input_constructible_for<value_type> R, class... Out>
    requires (sizeof...(Out) <= 1)
    static constexpr result<void, input_value_t<R>> _impl(Call call, R&& r, Out&... out)
    {
        input_span input{ std::forward<R>(r) };
        using V = input_value_t<R>;

        while (true)
        {
            if constexpr (sizeof...(Out) == 0)
            {
                result<void, V> res = call(P{}, input);
                input = res.remaining();
                if (not res.has_value())
                    break;
            }
            else
            {
                typename P::template result_for<V> element;
                result<void, V> res = call(P{}, input, element);
                input = res.remaining();
                if (not res.has_value())
                    break;
                (..., push(out, std::move(element)));
            }
        }
        return { success_tag, input };
    }
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_PARSERS_ZERO_OR_MORE_HPP
