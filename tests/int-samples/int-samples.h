#pragma once
#include <k3/tok3n.h>

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

template <class... Ts>
requires (... and std::same_as<Ts, int>)
consteval auto e(Ts... ts)
{
    return std::array<int, sizeof...(Ts)>{ ts... };
}

using namespace k3::tok3n;

#include "int-samples/basic.h"
#include "int-samples/macros.h"

#define ASSEMBLY "int"
