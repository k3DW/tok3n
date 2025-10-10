// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework/Assert.hpp"
#include <concepts>
#include <k3/tok3n/detail/cpo.hpp>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <variant>

FIXTURE("cpo emplace");

namespace {

struct Emplace {
    template <std::size_t I>
    constexpr std::size_t emplace(std::size_t i) { return i * I + 1; }
    template <std::size_t I>
    constexpr std::size_t emplace(std::size_t i) const { return i * I + 2; }
};

} // namespace

using namespace k3::tok3n;

template <class... Values>
requires (sizeof...(Values) >= 3 and (... and std::convertible_to<int, Values>))
void variant_emplace_test()
{
    using Variant = std::variant<Values...>;

    SIMPLE_EXPECT((detail::emplaceable<Variant&, int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Variant&, const int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Variant&, int&&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Variant&, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Variant&, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Variant&, const int, 0>));

    SIMPLE_EXPECT((detail::emplaceable<Variant&&, int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Variant&&, const int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Variant&&, int&&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Variant&&, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Variant&&, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Variant&&, const int, 0>));

    SIMPLE_EXPECT((not detail::emplaceable<const Variant&, int&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant&, const int&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant&, int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant&, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant&, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant&, const int, 0>));

    SIMPLE_EXPECT((not detail::emplaceable<const Variant&&, int&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant&&, const int&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant&&, int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant&&, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant&&, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant&&, const int, 0>));

    SIMPLE_EXPECT((detail::emplaceable<Variant, int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Variant, const int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Variant, int&&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Variant, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Variant, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Variant, const int, 0>));

    SIMPLE_EXPECT((not detail::emplaceable<const Variant, int&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant, const int&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant, int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Variant, const int, 0>));
}

TEST("cpo emplace", "std::variant")
{
    variant_emplace_test<int, short, std::size_t>();
    variant_emplace_test<std::int8_t, std::int16_t, std::int32_t>();
}

TEST("cpo emplace", "custom emplacer")
{
    SIMPLE_EXPECT((detail::emplaceable<Emplace&, int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Emplace&, const int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Emplace&, int&&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Emplace&, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Emplace&, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Emplace&, const int, 0>));

    SIMPLE_EXPECT((detail::emplaceable<Emplace&&, int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Emplace&&, const int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Emplace&&, int&&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Emplace&&, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Emplace&&, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Emplace&&, const int, 0>));

    SIMPLE_EXPECT((detail::emplaceable<const Emplace&, int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<const Emplace&, const int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<const Emplace&, int&&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<const Emplace&, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Emplace&, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Emplace&, const int, 0>));

    SIMPLE_EXPECT((detail::emplaceable<const Emplace&&, int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<const Emplace&&, const int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<const Emplace&&, int&&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<const Emplace&&, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Emplace&&, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Emplace&&, const int, 0>));

    SIMPLE_EXPECT((detail::emplaceable<Emplace, int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Emplace, const int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Emplace, int&&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<Emplace, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Emplace, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<Emplace, const int, 0>));

    SIMPLE_EXPECT((detail::emplaceable<const Emplace, int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<const Emplace, const int&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<const Emplace, int&&, 0>));
    SIMPLE_EXPECT((detail::emplaceable<const Emplace, const int&&, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Emplace, int, 0>));
    SIMPLE_EXPECT((not detail::emplaceable<const Emplace, const int, 0>));
}
