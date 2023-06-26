#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <StaticString str>
concept OneCharConstructible = (is_ascii(str)) and (is_sorted_and_uniqued(str));

template <StaticString str>
concept NotCharConstructible = (is_ascii(str)) and (is_sorted_and_uniqued(str));

template <StaticString str>
concept LiteralConstructible = (is_ascii(str));



template <StaticString str>
requires OneCharConstructible<str>
struct OneChar;

template <StaticString str>
requires NotCharConstructible<str>
struct NotChar;

template <StaticString str>
requires LiteralConstructible<str>
struct Literal;

} // namespace k3::tok3n