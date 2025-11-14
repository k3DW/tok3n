// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
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

    EXPECT_COMPILE_TIME((detail::gettable<Tup&, 0>));
    EXPECT_COMPILE_TIME((detail::gettable<Tup&, 1>));
    EXPECT_COMPILE_TIME((detail::gettable<Tup&, 2>));
    EXPECT_COMPILE_TIME((detail::gettable<Tup&&, 0>));
    EXPECT_COMPILE_TIME((detail::gettable<Tup&&, 1>));
    EXPECT_COMPILE_TIME((detail::gettable<Tup&&, 2>));
    EXPECT_COMPILE_TIME((detail::gettable<const Tup&, 0>));
    EXPECT_COMPILE_TIME((detail::gettable<const Tup&, 1>));
    EXPECT_COMPILE_TIME((detail::gettable<const Tup&, 2>));
    EXPECT_COMPILE_TIME((detail::gettable<const Tup&&, 0>));
    EXPECT_COMPILE_TIME((detail::gettable<const Tup&&, 1>));
    EXPECT_COMPILE_TIME((detail::gettable<const Tup&&, 2>));

    constexpr Tup tup{1, 2.0, 'c'};
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<0>(tup) == 1);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<1>(tup) == 2.0);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<2>(tup) == 'c');
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<0>(Tup{1, 2.0, 'c'}) == 1);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<1>(Tup{1, 2.0, 'c'}) == 2.0);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<2>(Tup{1, 2.0, 'c'}) == 'c');

    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<Tup&, 0>, int&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<Tup&, 1>, double&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<Tup&, 2>, char&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<Tup&&, 0>, int&&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<Tup&&, 1>, double&&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<Tup&&, 2>, char&&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const Tup&, 0>, const int&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const Tup&, 1>, const double&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const Tup&, 2>, const char&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const Tup&&, 0>, const int&&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const Tup&&, 1>, const double&&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const Tup&&, 2>, const char&&>));
}

TEST("cpo get", "adl get")
{
    EXPECT_COMPILE_TIME((detail::gettable<AdlGet&, 0>));
    EXPECT_COMPILE_TIME((detail::gettable<AdlGet&, 1>));
    EXPECT_COMPILE_TIME((detail::gettable<AdlGet&, 2>));
    EXPECT_COMPILE_TIME((detail::gettable<AdlGet&&, 0>));
    EXPECT_COMPILE_TIME((detail::gettable<AdlGet&&, 1>));
    EXPECT_COMPILE_TIME((detail::gettable<AdlGet&&, 2>));
    EXPECT_COMPILE_TIME((detail::gettable<const AdlGet&, 0>));
    EXPECT_COMPILE_TIME((detail::gettable<const AdlGet&, 1>));
    EXPECT_COMPILE_TIME((detail::gettable<const AdlGet&, 2>));
    EXPECT_COMPILE_TIME((detail::gettable<const AdlGet&&, 0>));
    EXPECT_COMPILE_TIME((detail::gettable<const AdlGet&&, 1>));
    EXPECT_COMPILE_TIME((detail::gettable<const AdlGet&&, 2>));

    constexpr AdlGet a;
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<0>(a) == 1);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<1>(a) == 3);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<2>(a) == 5);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<3>(a) == 7);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<0>(AdlGet{}) == 1);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<1>(AdlGet{}) == 3);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<2>(AdlGet{}) == 5);
    EXPECT_COMPILE_AND_RUN_TIME(detail::get_<3>(AdlGet{}) == 7);

    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<AdlGet&, 0>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<AdlGet&, 1>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<AdlGet&, 2>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<AdlGet&&, 0>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<AdlGet&&, 1>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<AdlGet&&, 2>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const AdlGet&, 0>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const AdlGet&, 1>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const AdlGet&, 2>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const AdlGet&&, 0>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const AdlGet&&, 1>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::get_t<const AdlGet&&, 2>, std::size_t>));
}
