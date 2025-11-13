// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <k3/tok3n/detail/cpo.hpp>
#include <deque>
#include <vector>
#include <utility>

FIXTURE("cpo index");

namespace {

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

} // namespace

using namespace k3::tok3n;

TEST("cpo index", "std::vector")
{
    using Vec = std::vector<int>;

    SIMPLE_EXPECT((detail::indexable<Vec&>));
    SIMPLE_EXPECT((detail::indexable<Vec&&>));
    SIMPLE_EXPECT((detail::indexable<const Vec&>));
    SIMPLE_EXPECT((detail::indexable<const Vec&&>));
    SIMPLE_EXPECT((not detail::indexable<Vec>));
    SIMPLE_EXPECT((not detail::indexable<const Vec>));

    SIMPLE_EXPECT(detail::index(Vec{9, 8, 7}, 0) == 9);
    SIMPLE_EXPECT(detail::index(Vec{9, 8, 7}, 1) == 8);
    SIMPLE_EXPECT(detail::index(Vec{9, 8, 7}, 2) == 7);

    SIMPLE_EXPECT((std::same_as<detail::index_t<Vec&>, int&>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<Vec&&>, int&>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<const Vec&>, const int&>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<const Vec&&>, const int&>));
}

TEST("cpo index", "std::deque")
{
    using Deq = std::deque<int>;

    SIMPLE_EXPECT((detail::indexable<Deq&>));
    SIMPLE_EXPECT((detail::indexable<Deq&&>));
    SIMPLE_EXPECT((detail::indexable<const Deq&>));
    SIMPLE_EXPECT((detail::indexable<const Deq&&>));
    SIMPLE_EXPECT((not detail::indexable<Deq>));
    SIMPLE_EXPECT((not detail::indexable<const Deq>));

    SIMPLE_EXPECT((std::same_as<detail::index_t<Deq&>, int&>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<Deq&&>, int&>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<const Deq&>, const int&>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<const Deq&&>, const int&>));
}

TEST("cpo index", "Unchecked")
{
    SIMPLE_EXPECT((detail::indexable<Unchecked&>));
    SIMPLE_EXPECT((detail::indexable<Unchecked&&>));
    SIMPLE_EXPECT((detail::indexable<const Unchecked&>));
    SIMPLE_EXPECT((detail::indexable<const Unchecked&&>));
    SIMPLE_EXPECT((not detail::indexable<Unchecked>));
    SIMPLE_EXPECT((not detail::indexable<const Unchecked>));

    Unchecked u;
    SIMPLE_EXPECT(detail::index(u, 0) == 1);
    SIMPLE_EXPECT(detail::index(u, 1) == 2);
    SIMPLE_EXPECT(detail::index(u, 2) == 3);
    SIMPLE_EXPECT(detail::index(std::as_const(u), 0) == 2);
    SIMPLE_EXPECT(detail::index(std::as_const(u), 1) == 3);
    SIMPLE_EXPECT(detail::index(std::as_const(u), 2) == 4);
    SIMPLE_EXPECT(detail::index(Unchecked{}, 0) == 3);
    SIMPLE_EXPECT(detail::index(Unchecked{}, 1) == 4);
    SIMPLE_EXPECT(detail::index(Unchecked{}, 2) == 5);
    SIMPLE_EXPECT(detail::index(static_cast<const Unchecked&&>(u), 0) == 4);
    SIMPLE_EXPECT(detail::index(static_cast<const Unchecked&&>(u), 1) == 5);
    SIMPLE_EXPECT(detail::index(static_cast<const Unchecked&&>(u), 2) == 6);

    SIMPLE_EXPECT((std::same_as<detail::index_t<Unchecked&>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<Unchecked&&>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<const Unchecked&>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<const Unchecked&&>, std::size_t>));
}

TEST("cpo index", "Checked")
{
    SIMPLE_EXPECT((detail::indexable<Checked&>));
    SIMPLE_EXPECT((detail::indexable<Checked&&>));
    SIMPLE_EXPECT((detail::indexable<const Checked&>));
    SIMPLE_EXPECT((detail::indexable<const Checked&&>));
    SIMPLE_EXPECT((not detail::indexable<Checked>));
    SIMPLE_EXPECT((not detail::indexable<const Checked>));

    Checked c;
    SIMPLE_EXPECT(detail::index(c, 0) == 5);
    SIMPLE_EXPECT(detail::index(c, 1) == 6);
    SIMPLE_EXPECT(detail::index(c, 2) == 7);
    SIMPLE_EXPECT(detail::index(std::as_const(c), 0) == 6);
    SIMPLE_EXPECT(detail::index(std::as_const(c), 1) == 7);
    SIMPLE_EXPECT(detail::index(std::as_const(c), 2) == 8);
    SIMPLE_EXPECT(detail::index(Checked{}, 0) == 7);
    SIMPLE_EXPECT(detail::index(Checked{}, 1) == 8);
    SIMPLE_EXPECT(detail::index(Checked{}, 2) == 9);
    SIMPLE_EXPECT(detail::index(static_cast<const Checked&&>(c), 0) == 8);
    SIMPLE_EXPECT(detail::index(static_cast<const Checked&&>(c), 1) == 9);
    SIMPLE_EXPECT(detail::index(static_cast<const Checked&&>(c), 2) == 10);

    SIMPLE_EXPECT((std::same_as<detail::index_t<Checked&>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<Checked&&>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<const Checked&>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<const Checked&&>, std::size_t>));
}

TEST("cpo index", "prefer checked indexing")
{
    SIMPLE_EXPECT((detail::indexable<Both&>));
    SIMPLE_EXPECT((detail::indexable<Both&&>));
    SIMPLE_EXPECT((detail::indexable<const Both&>));
    SIMPLE_EXPECT((detail::indexable<const Both&&>));
    SIMPLE_EXPECT((not detail::indexable<Both>));
    SIMPLE_EXPECT((not detail::indexable<const Both>));

    Both b;
    SIMPLE_EXPECT(detail::index(b, 0) == 5);
    SIMPLE_EXPECT(detail::index(b, 1) == 6);
    SIMPLE_EXPECT(detail::index(b, 2) == 7);
    SIMPLE_EXPECT(detail::index(std::as_const(b), 0) == 6);
    SIMPLE_EXPECT(detail::index(std::as_const(b), 1) == 7);
    SIMPLE_EXPECT(detail::index(std::as_const(b), 2) == 8);
    SIMPLE_EXPECT(detail::index(Both{}, 0) == 7);
    SIMPLE_EXPECT(detail::index(Both{}, 1) == 8);
    SIMPLE_EXPECT(detail::index(Both{}, 2) == 9);
    SIMPLE_EXPECT(detail::index(static_cast<const Both&&>(b), 0) == 8);
    SIMPLE_EXPECT(detail::index(static_cast<const Both&&>(b), 1) == 9);
    SIMPLE_EXPECT(detail::index(static_cast<const Both&&>(b), 2) == 10);

    SIMPLE_EXPECT((std::same_as<detail::index_t<Both&>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<Both&&>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<const Both&>, std::size_t>));
    SIMPLE_EXPECT((std::same_as<detail::index_t<const Both&&>, std::size_t>));
}
