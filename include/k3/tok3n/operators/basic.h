#pragma once
#include <k3/tok3n/parsers/basic/AnyOf.h>
#include <k3/tok3n/parsers/basic/NoneOf.h>
#include <k3/tok3n/parsers/basic/AllOf.h>
#include <k3/tok3n/parsers/adaptor/Ignore.h>

namespace k3::tok3n {

template <StaticArray arr>
constexpr auto any = AnyOf<detail::sort_and_unique<arr>()>{};

template <auto t, auto... ts>
requires (... and std::constructible_from<std::remove_cvref_t<decltype(t)>, decltype(ts)>)
constexpr auto any_of = any<StaticArray<std::remove_cvref_t<decltype(t)>, 1 + sizeof...(ts)>{ t, ts... }>;

template <StaticArray arr>
constexpr auto none = NoneOf<detail::sort_and_unique<arr>()>{};

template <auto t, auto... ts>
requires (... and std::constructible_from<std::remove_cvref_t<decltype(t)>, decltype(ts)>)
constexpr auto none_of = none<StaticArray<std::remove_cvref_t<decltype(t)>, 1 + sizeof...(ts)>{ t, ts... }>;

template <StaticArray arr>
constexpr auto all = AllOf<arr>{};

template <auto t, auto... ts>
requires (... and std::constructible_from<std::remove_cvref_t<decltype(t)>, decltype(ts)>)
constexpr auto all_of = all<StaticArray<std::remove_cvref_t<decltype(t)>, 1 + sizeof...(ts)>{ t, ts... }>;

template <StaticArray arr>
constexpr auto ign = Ignore<AllOf<arr>>{};



template <class T>
constexpr auto anything = NoneOf<StaticArray<T, 0>{}>{};

template <class T>
constexpr auto nothing = AnyOf<StaticArray<T, 0>{}>{};

template <class T>
constexpr auto eps = AllOf<StaticArray<T, 0>{}>{};



template <StaticArray arr>
consteval auto operator"" _any()
{
	return any<arr>;
}

template <StaticArray arr>
consteval auto operator"" _any_of()
{
	return any<arr>;
}

template <StaticArray arr>
consteval auto operator"" _none()
{
	return none<arr>;
}

template <StaticArray arr>
consteval auto operator"" _none_of()
{
	return none<arr>;
}

template <StaticArray arr>
consteval auto operator"" _all()
{
	return all<arr>;
}

template <StaticArray arr>
consteval auto operator"" _all_of()
{
	return all<arr>;
}

template <StaticArray arr>
consteval auto operator"" _ign()
{
	return ign<arr>;
}

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::any;
using ::k3::tok3n::any_of;
using ::k3::tok3n::none;
using ::k3::tok3n::none_of;
using ::k3::tok3n::all;
using ::k3::tok3n::all_of;
using ::k3::tok3n::ign;

using ::k3::tok3n::operator""_any;
using ::k3::tok3n::operator""_any_of;
using ::k3::tok3n::operator""_none;
using ::k3::tok3n::operator""_none_of;
using ::k3::tok3n::operator""_all;
using ::k3::tok3n::operator""_all_of;
using ::k3::tok3n::operator""_ign;

} // namespace k3::tok3n::operators
