#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticArray arr>
struct BasicTraits<AllOf<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = arr.size();

	template <std::convertible_to<value_type> V>
	static constexpr bool failure_condition(Input<V> input)
	{
		return (input.size() < length) || (Input(arr.span()) != input.first(length));
	}
};

template <StaticArray arr>
struct AllOf : BasicBase<AllOf<arr>>
{
	static constexpr ParserFamily family = AllOfFamily;
};

template <StaticArray arr>
requires std::same_as<char, typename decltype(arr)::value_type>
constexpr auto pretty(AllOf<arr>)
{
	static_assert(std::same_as<char, typename decltype(arr)::value_type>, "Non-char parsers cannot be prettied at the moment.");
	return StaticArray("AllOf<\"") + arr + StaticArray("\">");
}

} // namespace k3::tok3n
