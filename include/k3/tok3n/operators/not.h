#pragma once
#include <k3/tok3n/parsers/basic/AnyOf.h>
#include <k3/tok3n/parsers/basic/NoneOf.h>

namespace k3::tok3n {

template <StaticArray arr>
consteval auto operator!(AnyOf<arr>)
{
	return NoneOf<arr>{};
}

template <StaticArray arr>
consteval auto operator!(NoneOf<arr>)
{
	return AnyOf<arr>{};
}

template <Parser P>
consteval auto operator!(P) = delete;

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator!;

} // namespace k3::tok3n::operators
