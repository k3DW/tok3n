#pragma once
#include <k3/tok3n/concepts/Parser.h>

namespace k3::tok3n {

template <class P, class V>
concept ParserFor =
	Parser<P> and
	detail::equality_comparable_with<V, typename P::value_type> and
	requires (Input<V> input)
	{
		typename P::template result_for<V>;
		P::parse(input);
		P::lookahead(input);
		{ P::parse(input) } -> k3::tok3n::IsResult<typename P::template result_for<V>, V>;
		{ P::lookahead(input) } -> k3::tok3n::IsResult<void, V>;
	};

} // namespace k3::tok3n
