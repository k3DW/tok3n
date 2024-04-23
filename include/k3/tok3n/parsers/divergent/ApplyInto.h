#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, class T>
struct ApplyInto
{
	using value_type = typename P::value_type;

	template <InputConstructibleFor<value_type> R, class V = typename decltype(Input{ std::declval<R>() })::value_type>
	static constexpr bool parsable_range = detail::IsApplyable<detail::Construct<T>, typename P::template result_for<V>>;

	template <EqualityComparableWith<value_type> V>
	using result_for = T;

	static constexpr ParserFamily family = ApplyIntoFamily;

	template <InputConstructibleFor<value_type> R>
	requires parsable_range<R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		auto result = P::parse(input);
		if (result.has_value())
			return Result<result_for<V>, V>{ success, std::apply(detail::Construct<result_for<V>>{}, std::move(*result)), result.remaining() };
		else
			return Result<result_for<V>, V>{ failure, input };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n
