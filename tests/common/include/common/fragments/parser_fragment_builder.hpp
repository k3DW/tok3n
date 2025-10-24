// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_PARSER_FRAGMENT_BUILDER_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_PARSER_FRAGMENT_BUILDER_HPP

#include <type_traits>
#include <k3/tok3n/detail/parser.hpp>

namespace k3::tok3n::tests {

template <class Fragment, class P>
concept is_parser_fragment =
    std::is_empty_v<Fragment> and
    requires { Fragment{}(P{}); };

template <class P, class... Fragments>
requires (... and is_parser_fragment<Fragments, P>)
struct parser_fragment_builder
{
    static_assert(detail::parser<P>, "Must use a parser type");
    void operator()() const
    {
        (..., Fragments{}(P{}));
    }
};

template <class P>
constexpr auto the_parser = parser_fragment_builder<P>{};

template <class P, class... Fragments, class Frag>
constexpr auto operator|(parser_fragment_builder<P, Fragments...>, Frag)
{
    return parser_fragment_builder<P, Fragments..., Frag>{};
}

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_PARSER_FRAGMENT_BUILDER_HPP
