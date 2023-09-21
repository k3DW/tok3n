#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <StaticArray arr>
concept AnyOfConstructible = is_sorted_and_uniqued(arr);

template <StaticArray arr>
concept NoneOfConstructible = is_sorted_and_uniqued(arr);



template <StaticArray arr>
requires AnyOfConstructible<arr>
struct AnyOf;

template <StaticArray arr>
requires NoneOfConstructible<arr>
struct NoneOf;

template <StaticArray arr>
struct Literal;

} // namespace k3::tok3n
