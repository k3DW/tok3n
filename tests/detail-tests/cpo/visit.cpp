// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <k3/tok3n/detail/cpo.hpp>
#include <utility>
#include <variant>

FIXTURE("cpo visit");

namespace {

struct Member
{
    constexpr std::size_t visit(std::size_t i) { return i + 1; }
    constexpr std::size_t visit(std::size_t i) const { return i + 2; }
};

struct Free {};
constexpr std::size_t visit(std::size_t i, Free&) { return i + 11; }
constexpr std::size_t visit(std::size_t i, const Free&) { return i + 12; }

struct MemberAndFree : Member, Free {};

} // namespace

using namespace k3::tok3n;

TEST("cpo visit", "std::variant")
{
    using Variant = std::variant<int, short, std::size_t>;
    constexpr Variant v1 = 1;
    constexpr Variant v2 = short{2};
    constexpr Variant v3 = std::size_t{3};
    constexpr auto visitor = [](auto x) { return static_cast<int>(x); };
    using Visitor [[maybe_unused]] = decltype(visitor);

    SIMPLE_EXPECT(detail::visit(v1, visitor) == 1);
    SIMPLE_EXPECT(detail::visit(v2, visitor) == 2);
    SIMPLE_EXPECT(detail::visit(v3, visitor) == 3);
    SIMPLE_EXPECT(detail::visit(std::as_const(v1), visitor) == 1);
    SIMPLE_EXPECT(detail::visit(std::as_const(v2), visitor) == 2);
    SIMPLE_EXPECT(detail::visit(std::as_const(v3), visitor) == 3);

    SIMPLE_EXPECT((detail::visitable<Variant&, Visitor&>));
    SIMPLE_EXPECT((detail::visitable<Variant&&, Visitor&>));
    SIMPLE_EXPECT((detail::visitable<const Variant&, Visitor&>));
    SIMPLE_EXPECT((detail::visitable<const Variant&&, Visitor&>));
    SIMPLE_EXPECT((not detail::visitable<Variant, Visitor&>));
    SIMPLE_EXPECT((not detail::visitable<const Variant, Visitor&>));

    SIMPLE_EXPECT((detail::visitable<Variant&, const Visitor&>));
    SIMPLE_EXPECT((detail::visitable<Variant&&, const Visitor&>));
    SIMPLE_EXPECT((detail::visitable<const Variant&, const Visitor&>));
    SIMPLE_EXPECT((detail::visitable<const Variant&&, const Visitor&>));
    SIMPLE_EXPECT((not detail::visitable<Variant, const Visitor&>));
    SIMPLE_EXPECT((not detail::visitable<const Variant, const Visitor&>));

    SIMPLE_EXPECT((detail::visitable<Variant&, Visitor&&>));
    SIMPLE_EXPECT((detail::visitable<Variant&&, Visitor&&>));
    SIMPLE_EXPECT((detail::visitable<const Variant&, Visitor&&>));
    SIMPLE_EXPECT((detail::visitable<const Variant&&, Visitor&&>));
    SIMPLE_EXPECT((not detail::visitable<Variant, Visitor&&>));
    SIMPLE_EXPECT((not detail::visitable<const Variant, Visitor&&>));

    SIMPLE_EXPECT((detail::visitable<Variant&, const Visitor&&>));
    SIMPLE_EXPECT((detail::visitable<Variant&&, const Visitor&&>));
    SIMPLE_EXPECT((detail::visitable<const Variant&, const Visitor&&>));
    SIMPLE_EXPECT((detail::visitable<const Variant&&, const Visitor&&>));
    SIMPLE_EXPECT((not detail::visitable<Variant, const Visitor&&>));
    SIMPLE_EXPECT((not detail::visitable<const Variant, const Visitor&&>));

    SIMPLE_EXPECT((not detail::visitable<Variant&, Visitor>));
    SIMPLE_EXPECT((not detail::visitable<Variant&&, Visitor>));
    SIMPLE_EXPECT((not detail::visitable<const Variant&, Visitor>));
    SIMPLE_EXPECT((not detail::visitable<const Variant&&, Visitor>));
    SIMPLE_EXPECT((not detail::visitable<Variant, Visitor>));
    SIMPLE_EXPECT((not detail::visitable<const Variant, Visitor>));

    SIMPLE_EXPECT((not detail::visitable<Variant&, const Visitor>));
    SIMPLE_EXPECT((not detail::visitable<Variant&&, const Visitor>));
    SIMPLE_EXPECT((not detail::visitable<const Variant&, const Visitor>));
    SIMPLE_EXPECT((not detail::visitable<const Variant&&, const Visitor>));
    SIMPLE_EXPECT((not detail::visitable<Variant, const Visitor>));
    SIMPLE_EXPECT((not detail::visitable<const Variant, const Visitor>));
}

template <class Container, int offset>
void visit_test()
{
    Container c;
    SIMPLE_EXPECT(detail::visit(c, std::size_t{0}) == 1 + offset);
    SIMPLE_EXPECT(detail::visit(std::as_const(c), std::size_t{0}) == 2 + offset);

    SIMPLE_EXPECT((detail::visitable<Container&, std::size_t&>));
    SIMPLE_EXPECT((detail::visitable<Container&, const std::size_t&>));
    SIMPLE_EXPECT((detail::visitable<Container&, std::size_t&&>));
    SIMPLE_EXPECT((detail::visitable<Container&, const std::size_t&&>));
    SIMPLE_EXPECT((not detail::visitable<Container&, std::size_t>));
    SIMPLE_EXPECT((not detail::visitable<Container&, const std::size_t>));

    SIMPLE_EXPECT((detail::visitable<Container&&, std::size_t&>));
    SIMPLE_EXPECT((detail::visitable<Container&&, const std::size_t&>));
    SIMPLE_EXPECT((detail::visitable<Container&&, std::size_t&&>));
    SIMPLE_EXPECT((detail::visitable<Container&&, const std::size_t&&>));
    SIMPLE_EXPECT((not detail::visitable<Container&&, std::size_t>));
    SIMPLE_EXPECT((not detail::visitable<Container&&, const std::size_t>));

    SIMPLE_EXPECT((detail::visitable<const Container&, std::size_t&>));
    SIMPLE_EXPECT((detail::visitable<const Container&, const std::size_t&>));
    SIMPLE_EXPECT((detail::visitable<const Container&, std::size_t&&>));
    SIMPLE_EXPECT((detail::visitable<const Container&, const std::size_t&&>));
    SIMPLE_EXPECT((not detail::visitable<const Container&, std::size_t>));
    SIMPLE_EXPECT((not detail::visitable<const Container&, const std::size_t>));

    SIMPLE_EXPECT((detail::visitable<const Container&&, std::size_t&>));
    SIMPLE_EXPECT((detail::visitable<const Container&&, const std::size_t&>));
    SIMPLE_EXPECT((detail::visitable<const Container&&, std::size_t&&>));
    SIMPLE_EXPECT((detail::visitable<const Container&&, const std::size_t&&>));
    SIMPLE_EXPECT((not detail::visitable<const Container&&, std::size_t>));
    SIMPLE_EXPECT((not detail::visitable<const Container&&, const std::size_t>));

    SIMPLE_EXPECT((not detail::visitable<Container, std::size_t&>));
    SIMPLE_EXPECT((not detail::visitable<Container, const std::size_t&>));
    SIMPLE_EXPECT((not detail::visitable<Container, std::size_t&&>));
    SIMPLE_EXPECT((not detail::visitable<Container, const std::size_t&&>));
    SIMPLE_EXPECT((not detail::visitable<Container, std::size_t>));
    SIMPLE_EXPECT((not detail::visitable<Container, const std::size_t>));

    SIMPLE_EXPECT((not detail::visitable<const Container, std::size_t&>));
    SIMPLE_EXPECT((not detail::visitable<const Container, const std::size_t&>));
    SIMPLE_EXPECT((not detail::visitable<const Container, std::size_t&&>));
    SIMPLE_EXPECT((not detail::visitable<const Container, const std::size_t&&>));
    SIMPLE_EXPECT((not detail::visitable<const Container, std::size_t>));
    SIMPLE_EXPECT((not detail::visitable<const Container, const std::size_t>));
}

TEST("cpo visit", "visit")
{
    visit_test<Member, 0>();
    visit_test<Free, 10>();
    visit_test<MemberAndFree, 0>(); // prefer member to free
}
