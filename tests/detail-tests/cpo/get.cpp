// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework/Assert.hpp"
#include <k3/tok3n/detail/cpo.hpp>
#include <tuple>

FIXTURE("cpo get");

namespace {

struct AdlGet {};

template <std::size_t I>
requires (I < 4)
constexpr auto get(AdlGet) {
    return I * 2 + 1;
}

} // namespace

using namespace k3::tok3n;

TEST("cpo get", "std::get")
{
    using Tup = std::tuple<int, double, char>;

    SIMPLE_EXPECT((detail::gettable<Tup&, 0>));
    SIMPLE_EXPECT((detail::gettable<Tup&, 1>));
    SIMPLE_EXPECT((detail::gettable<Tup&, 2>));
    SIMPLE_EXPECT((detail::gettable<Tup&&, 0>));
    SIMPLE_EXPECT((detail::gettable<Tup&&, 1>));
    SIMPLE_EXPECT((detail::gettable<Tup&&, 2>));
    SIMPLE_EXPECT((detail::gettable<const Tup&, 0>));
    SIMPLE_EXPECT((detail::gettable<const Tup&, 1>));
    SIMPLE_EXPECT((detail::gettable<const Tup&, 2>));
    SIMPLE_EXPECT((detail::gettable<const Tup&&, 0>));
    SIMPLE_EXPECT((detail::gettable<const Tup&&, 1>));
    SIMPLE_EXPECT((detail::gettable<const Tup&&, 2>));

    constexpr Tup tup{1, 2.0, 'c'};
    SIMPLE_EXPECT(detail::get_<0>(tup) == 1);
    SIMPLE_EXPECT(detail::get_<1>(tup) == 2.0);
    SIMPLE_EXPECT(detail::get_<2>(tup) == 'c');
    SIMPLE_EXPECT(detail::get_<0>(Tup{1, 2.0, 'c'}) == 1);
    SIMPLE_EXPECT(detail::get_<1>(Tup{1, 2.0, 'c'}) == 2.0);
    SIMPLE_EXPECT(detail::get_<2>(Tup{1, 2.0, 'c'}) == 'c');

    SIMPLE_EXPECT((std::same_as<detail::get_t<Tup&, 0>, int&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<Tup&, 1>, double&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<Tup&, 2>, char&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<Tup&&, 0>, int&&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<Tup&&, 1>, double&&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<Tup&&, 2>, char&&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const Tup&, 0>, const int&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const Tup&, 1>, const double&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const Tup&, 2>, const char&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const Tup&&, 0>, const int&&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const Tup&&, 1>, const double&&>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const Tup&&, 2>, const char&&>));
}

TEST("cpo get", "adl get")
{
    SIMPLE_EXPECT((detail::gettable<AdlGet&, 0>));
    SIMPLE_EXPECT((detail::gettable<AdlGet&, 1>));
    SIMPLE_EXPECT((detail::gettable<AdlGet&, 2>));
    SIMPLE_EXPECT((detail::gettable<AdlGet&&, 0>));
    SIMPLE_EXPECT((detail::gettable<AdlGet&&, 1>));
    SIMPLE_EXPECT((detail::gettable<AdlGet&&, 2>));
    SIMPLE_EXPECT((detail::gettable<const AdlGet&, 0>));
    SIMPLE_EXPECT((detail::gettable<const AdlGet&, 1>));
    SIMPLE_EXPECT((detail::gettable<const AdlGet&, 2>));
    SIMPLE_EXPECT((detail::gettable<const AdlGet&&, 0>));
    SIMPLE_EXPECT((detail::gettable<const AdlGet&&, 1>));
    SIMPLE_EXPECT((detail::gettable<const AdlGet&&, 2>));

    constexpr AdlGet a;
    SIMPLE_EXPECT(detail::get_<0>(a) == 1);
    SIMPLE_EXPECT(detail::get_<1>(a) == 3);
    SIMPLE_EXPECT(detail::get_<2>(a) == 5);
    SIMPLE_EXPECT(detail::get_<3>(a) == 7);
    SIMPLE_EXPECT(detail::get_<0>(AdlGet{}) == 1);
    SIMPLE_EXPECT(detail::get_<1>(AdlGet{}) == 3);
    SIMPLE_EXPECT(detail::get_<2>(AdlGet{}) == 5);
    SIMPLE_EXPECT(detail::get_<3>(AdlGet{}) == 7);

    SIMPLE_EXPECT((std::same_as<detail::get_t<AdlGet&, 0>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<AdlGet&, 1>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<AdlGet&, 2>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<AdlGet&&, 0>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<AdlGet&&, 1>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<AdlGet&&, 2>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const AdlGet&, 0>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const AdlGet&, 1>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const AdlGet&, 2>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const AdlGet&&, 0>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const AdlGet&&, 1>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::get_t<const AdlGet&&, 2>, std::size_t>));
}
