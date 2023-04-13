#pragma once
#include <tok3n/namespace.h>
#include <tok3n/concepts/Parser.h>

TOK3N_BEGIN_NAMESPACE()

template <Parser P>
struct ParserResultOf
{
	consteval ParserResultOf(P) {}

	template <class R>
	static constexpr bool is = std::same_as<typename P::result_type, R>;
};

TOK3N_END_NAMESPACE()
