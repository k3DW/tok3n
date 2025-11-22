// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <k3/k3tchup.hpp>
#include <k3/tok3n/detail/cpo.hpp>
#include <deque>
#include <vector>
#include <utility>

namespace k3::tok3n::tests {
namespace {

FIXTURE("cpo index");

struct Unchecked
{
    constexpr std::size_t operator[](std::size_t i) & { return i + 1; }
    constexpr std::size_t operator[](std::size_t i) const & { return i + 2; }
    constexpr std::size_t operator[](std::size_t i) && { return i + 3; }
    constexpr std::size_t operator[](std::size_t i) const && { return i + 4; }
};

struct Checked
{
    constexpr std::size_t at(std::size_t i) & { return i + 5; }
    constexpr std::size_t at(std::size_t i) const & { return i + 6; }
    constexpr std::size_t at(std::size_t i) && { return i + 7; }
    constexpr std::size_t at(std::size_t i) const && { return i + 8; }
};

struct Both : Unchecked, Checked {};

TEST("cpo index", "std::vector")
{
    using Vec = std::vector<int>;

    EXPECT_COMPILE_TIME((detail::indexable<Vec&>));
    EXPECT_COMPILE_TIME((detail::indexable<Vec&&>));
    EXPECT_COMPILE_TIME((detail::indexable<const Vec&>));
    EXPECT_COMPILE_TIME((detail::indexable<const Vec&&>));
    EXPECT_COMPILE_TIME((not detail::indexable<Vec>));
    EXPECT_COMPILE_TIME((not detail::indexable<const Vec>));

    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Vec{9, 8, 7}, 0) == 9);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Vec{9, 8, 7}, 1) == 8);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Vec{9, 8, 7}, 2) == 7);

    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<Vec&>, int&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<Vec&&>, int&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<const Vec&>, const int&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<const Vec&&>, const int&>));
}

TEST("cpo index", "std::deque")
{
    using Deq = std::deque<int>;

    EXPECT_COMPILE_TIME((detail::indexable<Deq&>));
    EXPECT_COMPILE_TIME((detail::indexable<Deq&&>));
    EXPECT_COMPILE_TIME((detail::indexable<const Deq&>));
    EXPECT_COMPILE_TIME((detail::indexable<const Deq&&>));
    EXPECT_COMPILE_TIME((not detail::indexable<Deq>));
    EXPECT_COMPILE_TIME((not detail::indexable<const Deq>));

    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<Deq&>, int&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<Deq&&>, int&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<const Deq&>, const int&>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<const Deq&&>, const int&>));
}

TEST("cpo index", "Unchecked")
{
    EXPECT_COMPILE_TIME((detail::indexable<Unchecked&>));
    EXPECT_COMPILE_TIME((detail::indexable<Unchecked&&>));
    EXPECT_COMPILE_TIME((detail::indexable<const Unchecked&>));
    EXPECT_COMPILE_TIME((detail::indexable<const Unchecked&&>));
    EXPECT_COMPILE_TIME((not detail::indexable<Unchecked>));
    EXPECT_COMPILE_TIME((not detail::indexable<const Unchecked>));

    Unchecked u;
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(u, 0) == 1);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(u, 1) == 2);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(u, 2) == 3);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(std::as_const(u), 0) == 2);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(std::as_const(u), 1) == 3);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(std::as_const(u), 2) == 4);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Unchecked{}, 0) == 3);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Unchecked{}, 1) == 4);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Unchecked{}, 2) == 5);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(static_cast<const Unchecked&&>(u), 0) == 4);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(static_cast<const Unchecked&&>(u), 1) == 5);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(static_cast<const Unchecked&&>(u), 2) == 6);

    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<Unchecked&>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<Unchecked&&>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<const Unchecked&>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<const Unchecked&&>, std::size_t>));
}

TEST("cpo index", "Checked")
{
    EXPECT_COMPILE_TIME((detail::indexable<Checked&>));
    EXPECT_COMPILE_TIME((detail::indexable<Checked&&>));
    EXPECT_COMPILE_TIME((detail::indexable<const Checked&>));
    EXPECT_COMPILE_TIME((detail::indexable<const Checked&&>));
    EXPECT_COMPILE_TIME((not detail::indexable<Checked>));
    EXPECT_COMPILE_TIME((not detail::indexable<const Checked>));

    Checked c;
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(c, 0) == 5);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(c, 1) == 6);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(c, 2) == 7);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(std::as_const(c), 0) == 6);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(std::as_const(c), 1) == 7);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(std::as_const(c), 2) == 8);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Checked{}, 0) == 7);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Checked{}, 1) == 8);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Checked{}, 2) == 9);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(static_cast<const Checked&&>(c), 0) == 8);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(static_cast<const Checked&&>(c), 1) == 9);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(static_cast<const Checked&&>(c), 2) == 10);

    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<Checked&>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<Checked&&>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<const Checked&>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<const Checked&&>, std::size_t>));
}

TEST("cpo index", "prefer checked indexing")
{
    EXPECT_COMPILE_TIME((detail::indexable<Both&>));
    EXPECT_COMPILE_TIME((detail::indexable<Both&&>));
    EXPECT_COMPILE_TIME((detail::indexable<const Both&>));
    EXPECT_COMPILE_TIME((detail::indexable<const Both&&>));
    EXPECT_COMPILE_TIME((not detail::indexable<Both>));
    EXPECT_COMPILE_TIME((not detail::indexable<const Both>));

    Both b;
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(b, 0) == 5);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(b, 1) == 6);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(b, 2) == 7);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(std::as_const(b), 0) == 6);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(std::as_const(b), 1) == 7);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(std::as_const(b), 2) == 8);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Both{}, 0) == 7);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Both{}, 1) == 8);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(Both{}, 2) == 9);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(static_cast<const Both&&>(b), 0) == 8);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(static_cast<const Both&&>(b), 1) == 9);
    EXPECT_COMPILE_AND_RUN_TIME(detail::index(static_cast<const Both&&>(b), 2) == 10);

    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<Both&>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<Both&&>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<const Both&>, std::size_t>));
    EXPECT_COMPILE_TIME((std::same_as<detail::index_t<const Both&&>, std::size_t>));
}

} // namespace
} // namespace k3::tok3n::tests
