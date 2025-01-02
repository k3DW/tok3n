// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include "common.hpp"

#if defined(VALUE_TYPE_INT)

    #if defined(VALUE_TYPE_ENUM) || defined(VALUE_TYPE_STRUCTURAL) || defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    #error Can only define one VALUE_TYPE_XYZ macro.
    #endif
    
    constexpr int A = -1002;
    constexpr int B = -1001;
    constexpr int C = -1000;
    constexpr int D = -999;
    constexpr int X = 0;
    constexpr int Y = 10;
    constexpr int Z = 20;
    constexpr int Question = 100;
    constexpr int Com = 1000;
    constexpr int Space = 10000;
    constexpr int Dot = 100000;

    using value_type = int;

#elif defined(VALUE_TYPE_ENUM)

    #if defined(VALUE_TYPE_INT) || defined(VALUE_TYPE_STRUCTURAL) || defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    #error Can only define one VALUE_TYPE_XYZ macro.
    #endif

    enum class E
    {
        A,
        B,
        C,
        D,
        X,
        Y,
        Z,
        Question,
        Com,
        Space,
        Dot,
    };

    constexpr bool operator<(E lhs, E rhs)
    {
        using under = std::underlying_type_t<E>;
        return static_cast<under>(lhs) < static_cast<under>(rhs);
    }

    using value_type = E;

    using enum E;

#elif defined(VALUE_TYPE_STRUCTURAL)

    #if defined(VALUE_TYPE_INT) || defined(VALUE_TYPE_ENUM) || defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    #error Can only define one VALUE_TYPE_XYZ macro.
    #endif

    struct S
    {
        int x;
        int y;

        friend constexpr bool operator==(const S& lhs, const S& rhs) = default;
        friend constexpr auto operator<=>(const S& lhs, const S& rhs) = default;
    };

    #define ANY_VALUE_TYPE_STRUCTURAL
    using value_type = S;
    constexpr auto cmp = std::less<>{};

#elif defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)

    #if defined(VALUE_TYPE_INT) || defined(VALUE_TYPE_ENUM) || defined(VALUE_TYPE_STRUCTURAL)
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

    #define ANY_VALUE_TYPE_STRUCTURAL
    using value_type = S;
    constexpr auto cmp = std::equal_to<>{};

#else
#error Must define exactly one VALUE_TYPE_XYZ macro.
#endif

#if defined(ANY_VALUE_TYPE_STRUCTURAL)

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

#endif

#include "samples/helpers.hpp"

#include "samples/basic-non-char.hpp"
#include "samples/sub_parsers.hpp"

#include "samples/macros-non-char.hpp"
