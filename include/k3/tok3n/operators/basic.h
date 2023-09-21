#pragma once
#include <k3/tok3n/parsers/basic/AnyOf.h>
#include <k3/tok3n/parsers/basic/NoneOf.h>
#include <k3/tok3n/parsers/basic/AllOf.h>
#include <k3/tok3n/parsers/adaptor/Ignore.h>

namespace k3::tok3n {

template <StaticArray arr>
constexpr auto one = AnyOf<sort_and_unique<arr>()>{};

template <StaticArray arr>
constexpr auto not_ = NoneOf<sort_and_unique<arr>()>{};

template <StaticArray arr>
constexpr auto lit = AllOf<arr>{};

template <StaticArray arr>
constexpr auto ign = Ignore<AllOf<arr>>{};



template <StaticArray arr>
consteval auto operator"" _any()
{
	return one<arr>;
}

template <StaticArray arr>
consteval auto operator"" _none()
{
	return not_<arr>;
}

template <StaticArray arr>
consteval auto operator"" _all()
{
	return lit<arr>;
}

template <StaticArray arr>
consteval auto operator"" _ign()
{
	return ign<arr>;
}

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::one;
using ::k3::tok3n::not_;
using ::k3::tok3n::lit;
using ::k3::tok3n::ign;

using ::k3::tok3n::operator""_any;
using ::k3::tok3n::operator""_none;
using ::k3::tok3n::operator""_all;
using ::k3::tok3n::operator""_ign;

} // namespace k3::tok3n::operators
