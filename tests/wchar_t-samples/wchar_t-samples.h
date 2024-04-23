#pragma once
#include <k3/tok3n.h>

using namespace k3::tok3n;

inline namespace wchar_t_assembly {

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

#include "wchar_t-samples/adaptor.h"
#include "wchar_t-samples/basic.h"
#include "wchar_t-samples/classes.h"
#include "wchar_t-samples/compound.h"
#include "wchar_t-samples/divergent.h"
#include "wchar_t-samples/functions.h"
#include "wchar_t-samples/macros.h"
#include "wchar_t-samples/repeat.h"

} // inline namespace wchar_t_assembly

#define ASSEMBLY "wchar_t"
