#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <StaticArray arr>
concept AnyOfConstructible = detail::SortedAndUniqued<arr>;

template <StaticArray arr>
concept NoneOfConstructible = detail::SortedAndUniqued<arr>;



template <StaticArray arr>
requires AnyOfConstructible<arr>
struct AnyOf;

template <StaticArray arr>
requires NoneOfConstructible<arr>
struct NoneOf;

template <StaticArray arr>
struct AllOf;

template <class ValueType>
struct Anything;

template <class ValueType>
struct Epsilon;

} // namespace k3::tok3n
