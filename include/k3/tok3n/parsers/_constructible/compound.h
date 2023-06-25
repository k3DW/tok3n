#pragma once
#include <k3/tok3n/concepts/Parser.h>
#include <k3/tok3n/detail/all_same.h>

namespace k3::tok3n::constructible {

template <class... Ps>
concept Choice =
	(Parser<Ps> and ...) and
	(sizeof...(Ps) >= 2) and
	k3::tok3n::detail::all_same<typename Ps::result_type...>;

template <class... Ps>
concept Sequence =
	(Parser<Ps> and ...) and
	(sizeof...(Ps) >= 2);

} // namespace k3::tok3n::constructible
