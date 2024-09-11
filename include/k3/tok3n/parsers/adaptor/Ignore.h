#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <k3/tok3n/detail/parser.h>

namespace k3::tok3n {

template <detail::parser P>
struct Ignore
{
	using value_type = typename P::value_type;
	
	template <detail::equality_comparable_with<value_type> V>
	using result_for = detail::front<void, V>;

	static constexpr detail::parser_family family = detail::ignore_family;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n
