// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <k3/k3tchup.hpp>
#include <k3/tok3n/detail/cpo.hpp>
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <variant>

namespace k3::tok3n::tests {
namespace {

FIXTURE("cpo emplace");

struct Emplace {
    template <std::size_t I>
    constexpr std::size_t emplace(std::size_t i) { return i * I + 1; }
    template <std::size_t I>
    constexpr std::size_t emplace(std::size_t i) const { return i * I + 2; }
};

template <class... Values>
requires (sizeof...(Values) >= 3 and (... and std::convertible_to<int, Values>))
void variant_emplace_test()
{
    using Variant = std::variant<Values...>;

    EXPECT_COMPILE_TIME((detail::emplaceable<Variant&, int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Variant&, const int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Variant&, int&&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Variant&, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Variant&, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Variant&, const int, 0>));

    EXPECT_COMPILE_TIME((detail::emplaceable<Variant&&, int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Variant&&, const int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Variant&&, int&&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Variant&&, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Variant&&, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Variant&&, const int, 0>));

    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&, int&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&, const int&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&, int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&, const int, 0>));

    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&&, int&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&&, const int&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&&, int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&&, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&&, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant&&, const int, 0>));

    EXPECT_COMPILE_TIME((detail::emplaceable<Variant, int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Variant, const int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Variant, int&&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Variant, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Variant, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Variant, const int, 0>));

    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant, int&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant, const int&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant, int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Variant, const int, 0>));
}

TEST("cpo emplace", "std::variant")
{
    variant_emplace_test<int, short, std::size_t>();
    variant_emplace_test<std::int8_t, std::int16_t, std::int32_t>();
}

TEST("cpo emplace", "custom emplacer")
{
    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace&, int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace&, const int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace&, int&&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace&, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Emplace&, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Emplace&, const int, 0>));

    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace&&, int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace&&, const int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace&&, int&&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace&&, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Emplace&&, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Emplace&&, const int, 0>));

    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace&, int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace&, const int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace&, int&&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace&, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Emplace&, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Emplace&, const int, 0>));

    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace&&, int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace&&, const int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace&&, int&&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace&&, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Emplace&&, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Emplace&&, const int, 0>));

    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace, int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace, const int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace, int&&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<Emplace, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Emplace, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<Emplace, const int, 0>));

    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace, int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace, const int&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace, int&&, 0>));
    EXPECT_COMPILE_TIME((detail::emplaceable<const Emplace, const int&&, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Emplace, int, 0>));
    EXPECT_COMPILE_TIME((not detail::emplaceable<const Emplace, const int, 0>));
}

} // namespace
} // namespace k3::tok3n::tests
