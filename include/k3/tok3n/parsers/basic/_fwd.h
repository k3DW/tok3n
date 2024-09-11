#pragma once
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>

namespace k3::tok3n {

template <detail::static_array arr>
concept AnyOfConstructible = detail::is_sorted_and_uniqued(arr.span());

template <detail::static_array arr>
concept NoneOfConstructible = detail::is_sorted_and_uniqued(arr.span());



template <detail::static_array arr>
requires AnyOfConstructible<arr>
struct AnyOf;

template <detail::static_array arr>
requires NoneOfConstructible<arr>
struct NoneOf;

template <detail::static_array arr>
struct AllOf;

template <class ValueType>
struct Anything;

template <class ValueType>
struct Epsilon;

} // namespace k3::tok3n
