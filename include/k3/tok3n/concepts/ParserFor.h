#pragma once
#include <k3/tok3n/concepts/Parser.h>

namespace k3::tok3n {

namespace detail
{
	struct DoNotCareAboutResultTag {};
}

template <class P, class V, class R = detail::DoNotCareAboutResultTag>
concept ParserFor =
	Parser<P> and
	EqualityComparableWith<V, typename P::value_type> and
	requires (Input<V> input)
	{
		typename P::template result_for<V>;
		P::parse(input);
		P::lookahead(input);
		{ P::parse(input) } -> k3::tok3n::IsResult<typename P::template result_for<V>, V>;
		{ P::lookahead(input) } -> k3::tok3n::IsResult<void, V>;
	} and
	(
		std::same_as<R, detail::DoNotCareAboutResultTag> or
		std::same_as<typename P::template result_for<V>, R>
	);

} // namespace k3::tok3n
