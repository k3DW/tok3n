#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticArray> class Basic, StaticArray arr>
struct Join<Maybe<Basic<arr>>>
{
	using value_type = typename Basic<arr>::value_type;
	
	template <EqualityComparableWith<value_type> V>
	using result_for = Output<V>;

	static constexpr ParserFamily family = JoinFamily;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		using Traits = BasicTraits<Basic<arr>>;

		if (Traits::failure_condition(input))
			return Result<result_for<V>, V>{ success, { input.data(), 0 }, input };

		return Result<result_for<V>, V>{ success, { input.data(), Traits::length }, { input.data() + Traits::length, input.size() - Traits::length } };
	}
	
	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		using Traits = BasicTraits<Basic<arr>>;

		if (Traits::failure_condition(input))
			return Result<void, V>{ success, input };

		return Result<void, V>{ success, { input.data() + Traits::length, input.size() - Traits::length } };
	}
};

} // namespace k3::tok3n
