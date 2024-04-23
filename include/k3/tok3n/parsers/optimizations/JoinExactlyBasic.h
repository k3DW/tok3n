#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticArray> class Basic, StaticArray arr, IsConst<std::size_t> N>
struct Join<Exactly<Basic<arr>, N>>
{
	using value_type = typename Basic<arr>::value_type;
	
	template <EqualityComparableWith<value_type> V>
	using result_for = Output<V>;

	static constexpr ParserFamily family = JoinFamily;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		using Traits = BasicTraits<Basic<arr>>;

		const Input original_input = input;
		Output<V> result = { input.data(), 0 };

		for (std::size_t i = 0; i < N::value; i++)
		{
			if (Traits::failure_condition(input))
				return Result<result_for<V>, V>{ failure, original_input };
			result = { result.data(), result.size() + Traits::length };
			input = input.subspan(Traits::length);
		}

		return Result<result_for<V>, V>{ success, result, input };
	}
	
	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		using Traits = BasicTraits<Basic<arr>>;

		const Input original_input = input;

		for (std::size_t i = 0; i < N::value; i++)
		{
			if (Traits::failure_condition(input))
				return Result<void, V>{ failure, original_input };
			input = input.subspan(Traits::length);
		}

		return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
