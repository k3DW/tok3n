#pragma once
#include <k3/tok3n.h>

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

template <class... Ts>
requires (... and std::same_as<Ts, E>)
consteval auto e(Ts... ts)
{
    return std::array<E, sizeof...(Ts)>{ ts... };
}

using namespace k3::tok3n;

#include "enum-samples/basic.h"
#include "enum-samples/macros.h"

#define ASSEMBLY "enum"
