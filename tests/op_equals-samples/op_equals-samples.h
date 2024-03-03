#pragma once
#include <k3/tok3n.h>

struct S
{
    int x;
    int y;

    friend constexpr bool operator==(const S& lhs, const S& rhs)
    {
        return lhs.x == rhs.x;
    }
    friend constexpr auto operator<=>(const S& lhs, const S& rhs)
    {
        return lhs.x <=> rhs.x;
    }
};

namespace SS
{

    constexpr S A{ -10, 20 };
    constexpr S B{ -10, 50 };
    constexpr S C{ -5, -100 };
    constexpr S D{ -5, 0 };
    constexpr S X{ 0, 500 };
    constexpr S Y{ 1, 499 };
    constexpr S Z{ 2, 498 };
    constexpr S Question{ 100, 0 };
    constexpr S Com{ 1000, 0 };
    constexpr S Space{ 10000, 0 };
    constexpr S Dot{ 100000, 0 };

    static_assert(A == B);
    static_assert(B < C);
    static_assert(C == D);
    static_assert(D < X);
    static_assert(X < Y);
    static_assert(Y < Z);
    static_assert(Z < Question);
    static_assert(Question < Com);
    static_assert(Com < Space);
    static_assert(Space < Dot);

}

template <class... Ts>
requires (... and std::same_as<Ts, S>)
consteval auto e(Ts... ts)
{
    return std::array<S, sizeof...(Ts)>{ ts... };
}

using namespace k3::tok3n;

#include "op_equals-samples/basic.h"
#include "op_equals-samples/macros.h"

// Non-defaulted operator equals
#define ASSEMBLY "op_equals"
