#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <StaticString str>
requires LiteralConstructible<str>
struct BasicTraits<Literal<str>>
{
	static constexpr std::size_t length = str.size();

	static constexpr bool failure_condition(Input input)
	{
		return not input.starts_with(str.view());
	}
};

template <StaticString str>
requires LiteralConstructible<str>
struct Literal : BasicBase<Literal<str>>
{
	static constexpr ParserType type = LiteralType;
};

} // namespace k3::tok3n
