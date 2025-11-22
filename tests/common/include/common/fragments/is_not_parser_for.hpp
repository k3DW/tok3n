// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_NOT_PARSER_FOR_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_NOT_PARSER_FOR_HPP

#include <typeinfo>
#include <k3/k3tchup/assert.hpp>
#include <k3/tok3n/detail/parser.hpp>

namespace k3::tok3n::tests {

template <class ValueType>
struct is_not_parser_for_tag
{
    template <class P>
    void operator()(P) const
    {
        EXPECT_COMPILE_TIME((not detail::parser_for<P, ValueType>))
            << "`parser_for<P, V>` is satisfied, but it should not be.\n"
            << "[\n"
            << "    P = " << typeid(P).name() << "\n"
            << "    V = " << typeid(ValueType).name() << "\n"
            << "]";
    }
};
template <class ValueType>
constexpr auto is_not_parser_for = is_not_parser_for_tag<ValueType>{};

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_NOT_PARSER_FOR_HPP
