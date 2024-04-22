#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <vector>

namespace k3::tok3n {

template <Parser P>
struct Maybe;

template <Parser P, IsConst<std::size_t> N>
requires (N::value != 0)
struct Exactly;

template <Parser P>
struct OneOrMore;

template <Parser P>
struct ZeroOrMore;

template <Parser P, ParserCompatibleWith<P> D, IsConst<bool> KeepDelimiters>
struct Delimit;

} // namespace k3::tok3n
