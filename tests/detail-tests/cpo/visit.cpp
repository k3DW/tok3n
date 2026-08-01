// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <k3/k3tchup.hpp>
#include <k3/tok3n/detail/cpo.hpp>
#include <utility>
#include <variant>

namespace k3::tok3n::tests {
namespace {

FIXTURE("cpo visit");

struct Member
{
    constexpr std::size_t visit(std::size_t i) { return i + 1; }
    constexpr std::size_t visit(std::size_t i) const { return i + 2; }
};

struct Free {};
constexpr std::size_t visit(std::size_t i, Free&) { return i + 11; }
constexpr std::size_t visit(std::size_t i, const Free&) { return i + 12; }

struct MemberAndFree : Member, Free {};

TEST_CONSTEXPR("cpo visit", "std::variant", state)
{
    using Variant = std::variant<int, short, std::size_t>;
    Variant v1 = 1;
    Variant v2 = short{2};
    Variant v3 = std::size_t{3};
    constexpr auto visitor = [](auto x) { return static_cast<int>(x); };
    using Visitor [[maybe_unused]] = decltype(visitor);

    EXPECT_STATEFUL(state, detail::visit(v1, visitor) == 1);
    EXPECT_STATEFUL(state, detail::visit(v2, visitor) == 2);
    EXPECT_STATEFUL(state, detail::visit(v3, visitor) == 3);
    EXPECT_STATEFUL(state, detail::visit(std::as_const(v1), visitor) == 1);
    EXPECT_STATEFUL(state, detail::visit(std::as_const(v2), visitor) == 2);
    EXPECT_STATEFUL(state, detail::visit(std::as_const(v3), visitor) == 3);

    EXPECT_STATEFUL(state, (detail::visitable<Variant&, Visitor&>));
    EXPECT_STATEFUL(state, (detail::visitable<Variant&&, Visitor&>));
    EXPECT_STATEFUL(state, (detail::visitable<const Variant&, Visitor&>));
    EXPECT_STATEFUL(state, (detail::visitable<const Variant&&, Visitor&>));
    EXPECT_STATEFUL(state, (not detail::visitable<Variant, Visitor&>));
    EXPECT_STATEFUL(state, (not detail::visitable<const Variant, Visitor&>));

    EXPECT_STATEFUL(state, (detail::visitable<Variant&, const Visitor&>));
    EXPECT_STATEFUL(state, (detail::visitable<Variant&&, const Visitor&>));
    EXPECT_STATEFUL(state, (detail::visitable<const Variant&, const Visitor&>));
    EXPECT_STATEFUL(state, (detail::visitable<const Variant&&, const Visitor&>));
    EXPECT_STATEFUL(state, (not detail::visitable<Variant, const Visitor&>));
    EXPECT_STATEFUL(state, (not detail::visitable<const Variant, const Visitor&>));

    EXPECT_STATEFUL(state, (detail::visitable<Variant&, Visitor&&>));
    EXPECT_STATEFUL(state, (detail::visitable<Variant&&, Visitor&&>));
    EXPECT_STATEFUL(state, (detail::visitable<const Variant&, Visitor&&>));
    EXPECT_STATEFUL(state, (detail::visitable<const Variant&&, Visitor&&>));
    EXPECT_STATEFUL(state, (not detail::visitable<Variant, Visitor&&>));
    EXPECT_STATEFUL(state, (not detail::visitable<const Variant, Visitor&&>));

    EXPECT_STATEFUL(state, (detail::visitable<Variant&, const Visitor&&>));
    EXPECT_STATEFUL(state, (detail::visitable<Variant&&, const Visitor&&>));
    EXPECT_STATEFUL(state, (detail::visitable<const Variant&, const Visitor&&>));
    EXPECT_STATEFUL(state, (detail::visitable<const Variant&&, const Visitor&&>));
    EXPECT_STATEFUL(state, (not detail::visitable<Variant, const Visitor&&>));
    EXPECT_STATEFUL(state, (not detail::visitable<const Variant, const Visitor&&>));

    EXPECT_STATEFUL(state, (not detail::visitable<Variant&, Visitor>));
    EXPECT_STATEFUL(state, (not detail::visitable<Variant&&, Visitor>));
    EXPECT_STATEFUL(state, (not detail::visitable<const Variant&, Visitor>));
    EXPECT_STATEFUL(state, (not detail::visitable<const Variant&&, Visitor>));
    EXPECT_STATEFUL(state, (not detail::visitable<Variant, Visitor>));
    EXPECT_STATEFUL(state, (not detail::visitable<const Variant, Visitor>));

    EXPECT_STATEFUL(state, (not detail::visitable<Variant&, const Visitor>));
    EXPECT_STATEFUL(state, (not detail::visitable<Variant&&, const Visitor>));
    EXPECT_STATEFUL(state, (not detail::visitable<const Variant&, const Visitor>));
    EXPECT_STATEFUL(state, (not detail::visitable<const Variant&&, const Visitor>));
    EXPECT_STATEFUL(state, (not detail::visitable<Variant, const Visitor>));
    EXPECT_STATEFUL(state, (not detail::visitable<const Variant, const Visitor>));
}

template <class Container, int offset>
void visit_test()
{
    static constexpr auto packet = [](auto& state) {
        Container c;
        EXPECT_STATEFUL(state, detail::visit(c, std::size_t{0}) == 1 + offset);
        EXPECT_STATEFUL(state, detail::visit(std::as_const(c), std::size_t{0}) == 2 + offset);
    };
    EXPECT_THAT(packet);

    EXPECT_COMPILE_TIME((detail::visitable<Container&, std::size_t&>));
    EXPECT_COMPILE_TIME((detail::visitable<Container&, const std::size_t&>));
    EXPECT_COMPILE_TIME((detail::visitable<Container&, std::size_t&&>));
    EXPECT_COMPILE_TIME((detail::visitable<Container&, const std::size_t&&>));
    EXPECT_COMPILE_TIME((not detail::visitable<Container&, std::size_t>));
    EXPECT_COMPILE_TIME((not detail::visitable<Container&, const std::size_t>));

    EXPECT_COMPILE_TIME((detail::visitable<Container&&, std::size_t&>));
    EXPECT_COMPILE_TIME((detail::visitable<Container&&, const std::size_t&>));
    EXPECT_COMPILE_TIME((detail::visitable<Container&&, std::size_t&&>));
    EXPECT_COMPILE_TIME((detail::visitable<Container&&, const std::size_t&&>));
    EXPECT_COMPILE_TIME((not detail::visitable<Container&&, std::size_t>));
    EXPECT_COMPILE_TIME((not detail::visitable<Container&&, const std::size_t>));

    EXPECT_COMPILE_TIME((detail::visitable<const Container&, std::size_t&>));
    EXPECT_COMPILE_TIME((detail::visitable<const Container&, const std::size_t&>));
    EXPECT_COMPILE_TIME((detail::visitable<const Container&, std::size_t&&>));
    EXPECT_COMPILE_TIME((detail::visitable<const Container&, const std::size_t&&>));
    EXPECT_COMPILE_TIME((not detail::visitable<const Container&, std::size_t>));
    EXPECT_COMPILE_TIME((not detail::visitable<const Container&, const std::size_t>));

    EXPECT_COMPILE_TIME((detail::visitable<const Container&&, std::size_t&>));
    EXPECT_COMPILE_TIME((detail::visitable<const Container&&, const std::size_t&>));
    EXPECT_COMPILE_TIME((detail::visitable<const Container&&, std::size_t&&>));
    EXPECT_COMPILE_TIME((detail::visitable<const Container&&, const std::size_t&&>));
    EXPECT_COMPILE_TIME((not detail::visitable<const Container&&, std::size_t>));
    EXPECT_COMPILE_TIME((not detail::visitable<const Container&&, const std::size_t>));

    EXPECT_COMPILE_TIME((not detail::visitable<Container, std::size_t&>));
    EXPECT_COMPILE_TIME((not detail::visitable<Container, const std::size_t&>));
    EXPECT_COMPILE_TIME((not detail::visitable<Container, std::size_t&&>));
    EXPECT_COMPILE_TIME((not detail::visitable<Container, const std::size_t&&>));
    EXPECT_COMPILE_TIME((not detail::visitable<Container, std::size_t>));
    EXPECT_COMPILE_TIME((not detail::visitable<Container, const std::size_t>));

    EXPECT_COMPILE_TIME((not detail::visitable<const Container, std::size_t&>));
    EXPECT_COMPILE_TIME((not detail::visitable<const Container, const std::size_t&>));
    EXPECT_COMPILE_TIME((not detail::visitable<const Container, std::size_t&&>));
    EXPECT_COMPILE_TIME((not detail::visitable<const Container, const std::size_t&&>));
    EXPECT_COMPILE_TIME((not detail::visitable<const Container, std::size_t>));
    EXPECT_COMPILE_TIME((not detail::visitable<const Container, const std::size_t>));
}

TEST("cpo visit", "visit")
{
    visit_test<Member, 0>();
    visit_test<Free, 10>();
    visit_test<MemberAndFree, 0>(); // prefer member to free
}

} // namespace
} // namespace k3::tok3n::tests
