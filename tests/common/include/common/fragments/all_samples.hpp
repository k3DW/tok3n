// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_ALL_SAMPLES_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_ALL_SAMPLES_HPP

#include "common/samples_list.hpp"
#include <type_traits>

namespace k3::tok3n::tests {

struct all_samples_tag
{
    template <class F>
    requires std::is_empty_v<F>
    struct fragment
    {
        void operator()() const
        {
            []<detail::parser... Ps>(parser_list_t<Ps...>) {
                (..., F{}(Ps{}));
            }(samples_list<F>);
        }
    };
    struct satisfy_tag
    {
        template <class F>
        requires std::is_empty_v<F>
        constexpr fragment<F> operator()(F) const
        {
            return {};
        }
    };
    static constexpr auto satisfy = satisfy_tag{};
};
inline constexpr auto all_samples = all_samples_tag{};

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_ALL_SAMPLES_HPP
