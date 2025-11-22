// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_MODIFIER_VALUE_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_MODIFIER_VALUE_HPP

#include <typeinfo>
#include <k3/k3tchup/assert.hpp>
#include <k3/tok3n/detail/modifier.hpp>

namespace k3::tok3n::tests {

template <detail::modifier LHS>
struct modifier_value_tag
{
    template <detail::modifier RHS>
    struct is_fragment
    {
        void operator()() const
        {
            EXPECT_COMPILE_TIME((std::same_as<LHS, RHS>))
                << "`LHS` should be the same as `RHS`.\n"
                << "[\n"
                << "    LHS = " << typeid(LHS).name() << "\n"
                << "    RHS = " << typeid(RHS).name() << "\n"
                << "]";
        }
    };
    template <auto rhs>
    static constexpr auto is = is_fragment<std::remove_cvref_t<decltype(rhs)>>{};

    template <detail::modifier RHS>
    struct is_not_fragment
    {
        void operator()() const
        {
            EXPECT_COMPILE_TIME((not std::same_as<LHS, RHS>))
                << "`LHS` should not be the same as `RHS`.\n"
                << "[\n"
                << "    LHS = " << typeid(LHS).name() << "\n"
                << "    RHS = " << typeid(RHS).name() << "\n"
                << "]";
        }
    };
    template <auto rhs>
    static constexpr auto is_not = is_not_fragment<std::remove_cvref_t<decltype(rhs)>>{};
};

template <auto lhs>
constexpr auto modifier_value = modifier_value_tag<std::remove_cvref_t<decltype(lhs)>>{};

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_MODIFIER_VALUE_HPP
