#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/detail/head.h>

namespace k3::tok3n {

template <class ValueType>
struct Epsilon
{
	using value_type = ValueType;
	
	template <EqualityComparableWith<value_type> V>
	using result_for = detail::head<void, V>;

	static constexpr ParserFamily family = EpsilonFamily;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;
        return Result<void, V>{ success, input };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;
        return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
