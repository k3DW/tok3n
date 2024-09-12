#pragma once
#include <k3/tok3n/parsers/basic/AnyOf.h>
#include <k3/tok3n/parsers/basic/NoneOf.h>

namespace k3::tok3n {

template <detail::static_array arr>
constexpr auto operator!(AnyOf<arr>)
{
	return NoneOf<arr>{};
}

template <detail::static_array arr>
constexpr auto operator!(NoneOf<arr>)
{
	return AnyOf<arr>{};
}

template <detail::parser P>
constexpr auto operator!(P) = delete;

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator!;

} // namespace k3::tok3n::operators
