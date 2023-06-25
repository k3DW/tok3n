#pragma once
#include <k3/tok3n/parsers/_constructible/repeat.h>
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <Parser P>
requires constructible::Maybe<P>
struct Maybe
{
	using result_type = std::optional<typename P::result_type>;

	static constexpr ParserType type = MaybeType;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::move(*result), result.remaining() };
		else
			return { success, result_type{ std::nullopt }, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		auto result = P::lookahead(input);
		if (result.has_value())
			return { success, result.remaining() };
		else
			return { success, input };
	}
};

} // namespace k3::tok3n
