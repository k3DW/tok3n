#pragma once
#include <k3/tok3n/parsers/basic/OneChar.h>
#include <k3/tok3n/parsers/basic/NotChar.h>

namespace k3::tok3n {

template <StaticString str>
consteval auto operator!(OneChar<str>)
{
	return NotChar<str>{};
}

template <StaticString str>
consteval auto operator!(NotChar<str>)
{
	return OneChar<str>{};
}

template <Parser P>
consteval auto operator!(P) = delete;

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator!;

} // namespace k3::tok3n::operators
