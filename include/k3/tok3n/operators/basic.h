#pragma once
#include <k3/tok3n/parsers/basic/OneChar.h>
#include <k3/tok3n/parsers/basic/NotChar.h>
#include <k3/tok3n/parsers/basic/Literal.h>
#include <k3/tok3n/parsers/adaptor/Ignore.h>

namespace k3::tok3n::inline operators {

template <StaticString str>
requires (is_ascii(str))
constexpr auto one = OneChar<sort_and_unique<str>()>{};

template <StaticString str>
requires (is_ascii(str))
constexpr auto not_ = NotChar<sort_and_unique<str>()>{};

template <StaticString str>
requires (is_ascii(str))
constexpr auto lit = Literal<str>{};

template <StaticString str>
requires (is_ascii(str))
constexpr auto ign = Ignore<Literal<str>>{};



template <StaticString str>
requires (is_ascii(str))
consteval auto operator"" _one()
{
	return one<str>;
}

template <StaticString str>
requires (is_ascii(str))
consteval auto operator"" _not()
{
	return not_<str>;
}

template <StaticString str>
requires (is_ascii(str))
consteval auto operator"" _lit()
{
	return lit<str>;
}

template <StaticString str>
requires (is_ascii(str))
consteval auto operator"" _ign()
{
	return ign<str>;
}

} // namespace k3::tok3n::inline operators
