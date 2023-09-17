#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticArray arr>
struct BasicTraits<Literal<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = arr.size();

	static constexpr bool failure_condition(Input<value_type> input)
	{
		return (input.size() < length) || (Input(arr.span()) != input.first(length));
	}
};

template <StaticArray arr>
struct Literal : BasicBase<Literal<arr>>
{
	static constexpr ParserType type = LiteralType;
};

} // namespace k3::tok3n
