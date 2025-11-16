// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_PARSER_FAMILY_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_PARSER_FAMILY_HPP

#include "framework/assert.hpp"
#include <k3/tok3n/detail/static_array.hpp>

namespace k3::tok3n::tests {

template <template <k3::tok3n::detail::static_array> class Family>
struct the_basic_parser_family_tag
{
    template <k3::tok3n::detail::static_array arr>
    struct is_valid_with_fragment
    {
        void operator()() const
        {
            // Todo: Improve the streamed out error messages
            EXPECT_COMPILE_TIME((requires { typename Family<arr>; }))
                << "`Family` is not constructible from `arr`.";
        }
    };
    template <k3::tok3n::detail::static_array arr>
    static constexpr auto is_valid_with = is_valid_with_fragment<arr>{};

    template <k3::tok3n::detail::static_array arr>
    struct is_not_valid_with_fragment
    {
        void operator()() const
        {
            // Todo: Improve the streamed out error messages
            EXPECT_COMPILE_TIME((not requires { typename Family<arr>; }))
                << "`Family` is constructible from `arr`, but should not be.";
        }
    };
    template <k3::tok3n::detail::static_array arr>
    static constexpr auto is_not_valid_with = is_not_valid_with_fragment<arr>{};
};
template <template <k3::tok3n::detail::static_array> class Family>
constexpr auto the_basic_parser_family = the_basic_parser_family_tag<Family>{};

template <template <class...> class Family>
struct the_parser_family_tag
{
    template <class... Args>
    struct is_valid_with_fragment
    {
        void operator()() const
        {
            // Todo: Improve the streamed out error messages
            EXPECT_COMPILE_TIME((requires { typename Family<Args...>; }))
                << "`Family` is not constructible from `Args...`.";
        }
    };
    template <class... Args>
    static constexpr auto is_valid_with = is_valid_with_fragment<Args...>{};

    template <class... Args>
    struct is_not_valid_with_fragment
    {
        void operator()() const
        {
            // Todo: Improve the streamed out error messages
            EXPECT_COMPILE_TIME((not requires { typename Family<Args...>; }))
                << "`Family` is constructible from `Args...`, but should not be.";
        }
    };
    template <class... Args>
    static constexpr auto is_not_valid_with = is_not_valid_with_fragment<Args...>{};
};
template <template <class...> class Family>
constexpr auto the_parser_family = the_parser_family_tag<Family>{};

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_PARSER_FAMILY_HPP
