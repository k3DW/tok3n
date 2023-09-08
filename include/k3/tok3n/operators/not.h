#pragma once
#include <k3/tok3n/parsers/basic/OneChar.h>
#include <k3/tok3n/parsers/basic/NotChar.h>

namespace k3::tok3n {

template <StaticArray arr>
consteval auto operator!(OneChar<arr>)
{
	return NotChar<arr>{};
}

template <StaticArray arr>
consteval auto operator!(NotChar<arr>)
{
	return OneChar<arr>{};
}

template <Parser P>
consteval auto operator!(P) = delete;

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator!;

} // namespace k3::tok3n::operators
