// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <k3/tok3n/detail/cpo.hpp>
#include <cstdint>
#include <utility>
#include <vector>

namespace k3::tok3n::tests {
namespace {

FIXTURE("cpo push");

struct PushBack {
    constexpr int push_back(int i) { return i + 1; }
    constexpr int push_back(int i) const { return i + 2; }
};

struct Push {
    constexpr int push(int i) { return i + 11; }
    constexpr int push(int i) const { return i + 12; }
};

struct Insert {
    constexpr int insert(int i) { return i + 21; }
    constexpr int insert(int i) const { return i + 22; }
};

struct PushBackAndPush : PushBack, Push {};
struct PushBackAndInsert : PushBack, Insert {};
struct PushAndInsert : Push, Insert {};
struct AllThree : PushBack, Push, Insert {};

template <class Value>
void vector_container_test()
{
    using Container = std::vector<Value>;
    constexpr auto test = [](auto... xs)
    {
        Container c;
        (..., detail::push(c, xs));
        return c.size();
    };
    EXPECT_COMPILE_AND_RUN_TIME(test() == 0);
    EXPECT_COMPILE_AND_RUN_TIME(test(Value{1}) == 1);
    EXPECT_COMPILE_AND_RUN_TIME(test(Value{2}, Value{3}, Value{4}) == 3);
    EXPECT_COMPILE_AND_RUN_TIME(test(Value{5}, Value{6}, Value{7}, Value{8}, Value{9}, Value{10}) == 6);

    EXPECT_COMPILE_TIME((detail::pushable<Container&, Value&>));
    EXPECT_COMPILE_TIME((detail::pushable<Container&, const Value&>));
    EXPECT_COMPILE_TIME((detail::pushable<Container&, Value&&>));
    EXPECT_COMPILE_TIME((detail::pushable<Container&, const Value&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<Container&, Value>));
    EXPECT_COMPILE_TIME((not detail::pushable<Container&, const Value>));

    EXPECT_COMPILE_TIME((detail::pushable<Container&&, Value&>));
    EXPECT_COMPILE_TIME((detail::pushable<Container&&, const Value&>));
    EXPECT_COMPILE_TIME((detail::pushable<Container&&, Value&&>));
    EXPECT_COMPILE_TIME((detail::pushable<Container&&, const Value&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<Container&&, Value>));
    EXPECT_COMPILE_TIME((not detail::pushable<Container&&, const Value>));

    EXPECT_COMPILE_TIME((not detail::pushable<const Container&, Value&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container&, const Value&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container&, Value&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container&, const Value&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container&, Value>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container&, const Value>));

    EXPECT_COMPILE_TIME((not detail::pushable<const Container&&, Value&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container&&, const Value&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container&&, Value&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container&&, const Value&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container&&, Value>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container&&, const Value>));

    EXPECT_COMPILE_TIME((detail::pushable<Container, Value&>));
    EXPECT_COMPILE_TIME((detail::pushable<Container, const Value&>));
    EXPECT_COMPILE_TIME((detail::pushable<Container, Value&&>));
    EXPECT_COMPILE_TIME((detail::pushable<Container, const Value&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<Container, Value>));
    EXPECT_COMPILE_TIME((not detail::pushable<Container, const Value>));

    EXPECT_COMPILE_TIME((not detail::pushable<const Container, Value&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container, const Value&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container, Value&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container, const Value&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container, Value>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Container, const Value>));
}

TEST("cpo push", "std::vector")
{
    vector_container_test<int>();
    vector_container_test<std::size_t>();
    vector_container_test<std::uint8_t>();
}

template <class Pusher, int offset>
void pusher_test()
{
    Pusher p;
    EXPECT_COMPILE_AND_RUN_TIME(detail::push(p, 0) == 1 + offset);
    EXPECT_COMPILE_AND_RUN_TIME(detail::push(std::as_const(p), 0) == 2 + offset);

    EXPECT_COMPILE_TIME((detail::pushable<Pusher&, int&>));
    EXPECT_COMPILE_TIME((detail::pushable<Pusher&, const int&>));
    EXPECT_COMPILE_TIME((detail::pushable<Pusher&, int&&>));
    EXPECT_COMPILE_TIME((detail::pushable<Pusher&, const int&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<Pusher&, int>));
    EXPECT_COMPILE_TIME((not detail::pushable<Pusher&, const int>));

    EXPECT_COMPILE_TIME((detail::pushable<Pusher&&, int&>));
    EXPECT_COMPILE_TIME((detail::pushable<Pusher&&, const int&>));
    EXPECT_COMPILE_TIME((detail::pushable<Pusher&&, int&&>));
    EXPECT_COMPILE_TIME((detail::pushable<Pusher&&, const int&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<Pusher&&, int>));
    EXPECT_COMPILE_TIME((not detail::pushable<Pusher&&, const int>));

    EXPECT_COMPILE_TIME((detail::pushable<const Pusher&, int&>));
    EXPECT_COMPILE_TIME((detail::pushable<const Pusher&, const int&>));
    EXPECT_COMPILE_TIME((detail::pushable<const Pusher&, int&&>));
    EXPECT_COMPILE_TIME((detail::pushable<const Pusher&, const int&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Pusher&, int>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Pusher&, const int>));

    EXPECT_COMPILE_TIME((detail::pushable<const Pusher&&, int&>));
    EXPECT_COMPILE_TIME((detail::pushable<const Pusher&&, const int&>));
    EXPECT_COMPILE_TIME((detail::pushable<const Pusher&&, int&&>));
    EXPECT_COMPILE_TIME((detail::pushable<const Pusher&&, const int&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Pusher&&, int>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Pusher&&, const int>));

    EXPECT_COMPILE_TIME((detail::pushable<Pusher, int&>));
    EXPECT_COMPILE_TIME((detail::pushable<Pusher, const int&>));
    EXPECT_COMPILE_TIME((detail::pushable<Pusher, int&&>));
    EXPECT_COMPILE_TIME((detail::pushable<Pusher, const int&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<Pusher, int>));
    EXPECT_COMPILE_TIME((not detail::pushable<Pusher, const int>));

    EXPECT_COMPILE_TIME((detail::pushable<const Pusher, int&>));
    EXPECT_COMPILE_TIME((detail::pushable<const Pusher, const int&>));
    EXPECT_COMPILE_TIME((detail::pushable<const Pusher, int&&>));
    EXPECT_COMPILE_TIME((detail::pushable<const Pusher, const int&&>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Pusher, int>));
    EXPECT_COMPILE_TIME((not detail::pushable<const Pusher, const int>));
}

TEST("cpo push", "custom pushers")
{
    pusher_test<PushBack, 0>();
    pusher_test<Push, 10>();
    pusher_test<Insert, 20>();
    pusher_test<PushBackAndPush, 0>(); // prefer push_back to push
    pusher_test<PushBackAndInsert, 0>(); // prefer push_back to insert
    pusher_test<PushAndInsert, 10>(); // prefer push to insert
    pusher_test<AllThree, 0>(); // prefer push_back to the others
}

} // namespace
} // namespace k3::tok3n::tests
