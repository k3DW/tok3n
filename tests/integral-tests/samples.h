#pragma once
#include "pch.h"

#if defined(VALUE_TYPE_INT)

    #if defined(VALUE_TYPE_ENUM)
    #error Can only define one VALUE_TYPE_XYZ macro.
    #endif
    
    namespace E
    {
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
    };

    #define ASSEMBLY "int"
    using value_type = int;

    using namespace E;

#elif defined(VALUE_TYPE_ENUM)

    #if defined(VALUE_TYPE_INT)
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

    #define ASSEMBLY "enum"
    using value_type = E;

    using enum E;

#else
#error Must defined exactly one VALUE_TYPE_XYZ macro.
#endif

using namespace k3::tok3n;

#include "samples/helpers.ipp"

#include "samples/basic-integral.ipp"
#include "samples/sub_parsers.ipp"

#include "samples/macros-integral.ipp"

