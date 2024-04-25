#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>

namespace k3::tok3n {

template <class ValueType>
struct Anything
{
	using value_type = ValueType;
	
	template <EqualityComparableWith<value_type> V>
    using result_for = Output<V>;

	static constexpr ParserFamily family = AnythingFamily;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

        if (input.empty())
			return Result<result_for<V>, V>{ failure, input };
		else
			return Result<result_for<V>, V>{ success, { input.data(), 1 }, { input.data() + 1, input.size() - 1 } };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		if (input.empty())
			return Result<void, V>{ failure, input };
		else
			return Result<void, V>{ success, { input.data() + 1, input.size() - 1 } };
	}
};

} // namespace k3::tok3n
