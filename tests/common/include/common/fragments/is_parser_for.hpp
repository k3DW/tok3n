// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_PARSER_FOR_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_PARSER_FOR_HPP

#include "framework/assert.hpp"
#include <typeinfo>
#include <k3/tok3n/detail/parser.hpp>

namespace k3::tok3n::tests {

template <class ValueType>
struct is_parser_for_tag
{
    template <class ResultType>
    struct with_result_fragment
    {
        template <class P>
        void operator()(P) const
        {
            EXPECT_COMPILE_TIME((detail::parser_for<P, ValueType>))
                << "`parser_for<P, V>` is not satisfied.\n"
                << "[\n"
                << "    P = " << typeid(P).name() << "\n"
                << "    V = " << typeid(ValueType).name() << "\n"
                << "]";

            // The following EXPECT depends on the previous EXPECT,
            // and therefore this `if constexpr` is here so the code always compiles.
            if constexpr (detail::parser_for<P, ValueType>)
            {
                EXPECT_COMPILE_TIME((std::same_as<typename P::template result_for<ValueType>, ResultType>))
                    << "`P::result_for<V>` is not the given `result_type`.\n"
                    << "[\n"
                    << "    P           = " << typeid(P).name() << "\n"
                    << "    V           = " << typeid(ValueType).name() << "\n"
                    << "    result_type = " << typeid(ResultType).name() << "\n"
                    << "]";
            }
        }
    };
    template <class ResultType>
    static constexpr auto with_result = with_result_fragment<ResultType>{};
};
template <class ValueType>
constexpr auto is_parser_for = is_parser_for_tag<ValueType>{};

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_PARSER_FOR_HPP
