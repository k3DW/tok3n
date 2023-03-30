#pragma once
#include <tok3n/types/StaticString.h>

TOK3N_BEGIN_NAMESPACE(constructible)

template <StaticString str>
concept OneChar = is_ascii(str) && is_unique_and_sorted(str);

template <StaticString str>
concept NotChar = is_ascii(str) && is_unique_and_sorted(str);

template <StaticString str>
concept Literal = is_ascii(str);

TOK3N_END_NAMESPACE(constructible)
