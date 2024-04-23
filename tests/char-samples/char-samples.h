#pragma once
#include <k3/tok3n.h>

using namespace k3::tok3n;

inline namespace char_assembly {

#include "char-samples/adaptor.h"
#include "char-samples/basic.h"
#include "char-samples/classes.h"
#include "char-samples/compound.h"
#include "char-samples/divergent.h"
#include "char-samples/functions.h"
#include "char-samples/macros.h"
#include "char-samples/repeat.h"

template <class T, class... Ts>
requires (... and std::convertible_to<T, Ts>)
consteval auto e(Ts... ts)
{
    return std::array<T, sizeof...(Ts)>{ ts... };
}

template <class T, CharType U, std::size_t N>
requires std::convertible_to<T, U>
consteval auto e(const U(&us)[N])
{
    std::array<T, N - 1> arr;
    for (std::size_t i = 0; i != N - 1; ++i)
        arr[i] = us[i];
    return arr;
}

} // inline namespace char_assembly

#define ASSEMBLY "char"
