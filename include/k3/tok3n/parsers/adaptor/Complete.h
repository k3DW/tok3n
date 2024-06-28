#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <Parser P>
struct Complete
{
	using value_type = typename P::value_type;
	
	template <EqualityComparableWith<value_type> V>
	using result_for = typename P::template result_for<V>;

	static constexpr ParserFamily family = CompleteFamily;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		auto result = P::parse(input);
		if (not result.has_value() or not result.remaining().empty())
			return Result<result_for<V>, V>{ failure, input };
		else
			return result;
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		auto result = P::lookahead(input);
		if (not result.has_value() or not result.remaining().empty())
			return Result<void, V>{ failure, input };
		else
			return result;
	}
};

} // namespace k3::tok3n
