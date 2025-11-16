// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_ALL_PAIRS_OF_SAMPLES_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_ALL_PAIRS_OF_SAMPLES_HPP

#include "common/samples_list.hpp"
#include <type_traits>

namespace k3::tok3n::tests {

template <class LHSList, class RHSList>
struct pairs_of_samples_tag
{
    template <class F>
    requires std::is_empty_v<F>
    struct fragment
    {
    private:
        template <detail::parser LHS, detail::parser... RHS>
        static constexpr void inner_fn(LHS, parser_list_t<RHS...>)
        {
            (..., F{}(LHS{}, RHS{}));
        }
        template <detail::parser... LHS, detail::parser... RHS>
        static constexpr void fn(parser_list_t<LHS...>, parser_list_t<RHS...>)
        {
            (..., inner_fn(LHS{}, parser_list_t<RHS...>{}));
        }

    public:
        void operator()() const
        {
            if constexpr (std::is_void_v<LHSList> and std::is_void_v<RHSList>)
            {
                fn(samples_list<F>, samples_list<F>);
            }
            else
            {
                fn(LHSList{}, RHSList{});
            }
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

template <class LHS, class RHS>
inline constexpr auto pairs_of_samples = pairs_of_samples_tag<LHS, RHS>{};

inline constexpr auto all_pairs_of_samples = pairs_of_samples_tag<void, void>{};

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_ALL_PAIRS_OF_SAMPLES_HPP
