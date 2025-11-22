// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_HAS_VALUE_TYPE
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_HAS_VALUE_TYPE

#include <typeinfo>
#include <k3/k3tchup/assert.hpp>

namespace k3::tok3n::tests {

template <class ValueType>
struct has_value_type_fragment
{
    template <class P>
    void operator()(P) const
    {
        EXPECT_COMPILE_TIME((std::same_as<typename P::value_type, ValueType>))
            << "`P::value_type` is not the given `value_type`.\n"
            << "[\n"
            << "    P             = " << typeid(P).name() << "\n"
            << "    P::value_type = " << typeid(typename P::value_type).name() << "\n"
            << "    value_type    = " << typeid(ValueType).name() << "\n"
            << "]";
    }
};
template <class ValueType>
constexpr auto has_value_type = has_value_type_fragment<ValueType>{};

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_HAS_VALUE_TYPE
