#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>

namespace k3::tok3n {

template <detail::parser P>
struct Maybe;

template <detail::parser P, detail::integral_constant_of<std::size_t> N>
requires (N::value != 0)
struct Exactly;

template <detail::parser P>
struct OneOrMore;

template <detail::parser P>
struct ZeroOrMore;

template <detail::parser P, detail::parser_compatible_with<P> D, detail::integral_constant_of<bool> KeepDelimiters>
struct Delimit;

} // namespace k3::tok3n
