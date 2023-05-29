#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <k3/tok3n/parsers/_base/Basic.h>

TOK3N_BEGIN_NAMESPACE()

template <StaticString str>
requires (is_ascii(str))
struct Literal : detail::Basic<Literal<str>>
{
	static constexpr ParserType type = LiteralType;

	static constexpr std::size_t _length = str.size();

	static constexpr bool _failure_condition(Input input)
	{
		return not input.starts_with(str.view());
	}
};

TOK3N_END_NAMESPACE()
