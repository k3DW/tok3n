#pragma once

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

#define ASSEMBLY "enum"
using value_type = E;

using namespace k3::tok3n;

#include "samples/helpers.ipp"

#include "samples/basic-integral.ipp"
#include "samples/sub_parsers.ipp"

#include "samples/classes.ipp"
#include "samples/functions.ipp"
#include "samples/macros-integral.ipp"

#include "samples/adaptor.ipp"
#include "samples/compound.ipp"
#include "samples/divergent.ipp"
#include "samples/repeat.ipp"

using enum E;

constexpr bool operator<(E lhs, E rhs)
{
    using under = std::underlying_type_t<E>;
    return static_cast<under>(lhs) < static_cast<under>(rhs);
}
