#pragma once
#include <k3/tok3n/parsers/basic/OneChar.h>
#include <k3/tok3n/parsers/basic/NotChar.h>
#include <k3/tok3n/parsers/basic/Literal.h>
#include <k3/tok3n/parsers/adaptor/Ignore.h>

namespace k3::tok3n {

template <StaticArray arr>
constexpr auto one = OneChar<sort_and_unique<arr>()>{};

template <StaticArray arr>
constexpr auto not_ = NotChar<sort_and_unique<arr>()>{};

template <StaticArray arr>
constexpr auto lit = Literal<arr>{};

template <StaticArray arr>
constexpr auto ign = Ignore<Literal<arr>>{};



template <StaticArray arr>
consteval auto operator"" _one()
{
	return one<arr>;
}

template <StaticArray arr>
consteval auto operator"" _not()
{
	return not_<arr>;
}

template <StaticArray arr>
consteval auto operator"" _lit()
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

using ::k3::tok3n::operator""_one;
using ::k3::tok3n::operator""_not;
using ::k3::tok3n::operator""_lit;
using ::k3::tok3n::operator""_ign;

} // namespace k3::tok3n::operators
