#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <k3/tok3n/parsers/_base/Basic.h>

TOK3N_BEGIN_NAMESPACE()

template <StaticString str>
requires (is_ascii(str)) and (is_sorted_and_uniqued(str))
struct NotChar : detail::Basic<NotChar<str>>
{
	static constexpr ParserType type = NotCharType;

	static constexpr std::size_t _length = 1;

	static constexpr bool _failure_condition(Input input)
	{
		return input.empty() || str.contains(input.front());
	}
};

TOK3N_END_NAMESPACE()
