#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <StaticArray arr>
concept OneCharConstructible = is_sorted_and_uniqued(arr);

template <StaticArray arr>
concept NotCharConstructible = is_sorted_and_uniqued(arr);



template <StaticArray arr>
requires OneCharConstructible<arr>
struct OneChar;

template <StaticArray arr>
requires NotCharConstructible<arr>
struct NotChar;

template <StaticArray arr>
struct Literal;

} // namespace k3::tok3n
