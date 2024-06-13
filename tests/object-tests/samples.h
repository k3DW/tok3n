#pragma once
#include "pch.h"

#if defined(VALUE_TYPE_STRUCTURAL)

    #if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    #error Can only define one VALUE_TYPE_XYZ macro.
    #endif

    struct S
    {
        int x;
        int y;

        friend constexpr bool operator==(const S& lhs, const S& rhs) = default;
        friend constexpr auto operator<=>(const S& lhs, const S& rhs) = default;
    };

    #define ASSEMBLY "structural"
    using value_type = S;
    constexpr auto cmp = std::less<>{};

#elif defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)

    #if defined(VALUE_TYPE_STRUCTURAL)
    #error Can only define one VALUE_TYPE_XYZ macro.
    #endif

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

    #define ASSEMBLY "structural_op_equals"
    using value_type = S;
    constexpr auto cmp = std::equal_to<>{};

#else
#error Must define exactly one VALUE_TYPE_XYZ macro.
#endif

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

    static_assert(cmp(A, B));
    static_assert(B < C);
    static_assert(cmp(C, D));
    static_assert(D < X);
    static_assert(X < Y);
    static_assert(Y < Z);
    static_assert(Z < Question);
    static_assert(Question < Com);
    static_assert(Com < Space);
    static_assert(Space < Dot);

}

using namespace k3::tok3n;

#include "samples/helpers.ipp"

#include "samples/basic-object.ipp"
#include "samples/sub_parsers.ipp"

#include "samples/macros-object.ipp"

using namespace SS;
