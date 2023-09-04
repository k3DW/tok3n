#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticString str>
struct BasicTraits<Literal<str>>
{
	static constexpr std::size_t length = str.size();

	static constexpr bool failure_condition(Input<char> input)
	{
		return (input.size() < length) || (Input(str.span()) != input.first(length));
	}
};

template <StaticString str>
struct Literal : BasicBase<Literal<str>>
{
	static constexpr ParserType type = LiteralType;
};

} // namespace k3::tok3n
