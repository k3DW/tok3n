#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/detail/head.h>

namespace k3::tok3n {

template <Parser P, IsConst Value>
struct Constant
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = detail::head<typename Value::value_type, V>;

	static constexpr ParserFamily family = ConstantFamily;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		auto result = P::parse(input);
		if (result.has_value())
			return Result<result_for<V>, V>{ success, Value::value, result.remaining() };
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
