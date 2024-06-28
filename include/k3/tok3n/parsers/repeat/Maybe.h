#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P>
struct Maybe
{
	using value_type = typename P::value_type;

	template <InputConstructibleFor<value_type> R, class V = InputValueType<R>>
	static constexpr bool parsable_range = not std::same_as<typename P::template result_for<V>, void>;

	template <EqualityComparableWith<value_type> V>
	using result_for = std::optional<typename P::template result_for<V>>;

	static constexpr ParserFamily family = MaybeFamily;

	template <InputConstructibleFor<value_type> R>
	requires parsable_range<R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		auto result = P::parse(input);
		if (result.has_value())
			return Result<result_for<V>, V>{ success, std::move(*result), result.remaining() };
		else
			return Result<result_for<V>, V>{ success, result_for<V>{ std::nullopt }, input };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		auto result = P::lookahead(input);
		if (result.has_value())
			return Result<void, V>{ success, result.remaining() };
		else
			return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
