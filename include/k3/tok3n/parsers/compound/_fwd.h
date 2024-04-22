#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <k3/tok3n/detail/all_same.h>

namespace k3::tok3n {

template <class... Ps>
concept ChoiceConstructible =
	(Parser<Ps> and ...) and
	(sizeof...(Ps) >= 2) and
	detail::all_same<typename Ps::value_type...>;

template <class... Ps>
concept SequenceConstructible =
	(Parser<Ps> and ...) and
	(sizeof...(Ps) >= 2) and
	detail::all_same<typename Ps::value_type...>;



template <Parser... Ps>
requires ChoiceConstructible<Ps...>
struct Choice;

template <Parser... Ps>
requires SequenceConstructible<Ps...>
struct Sequence;

} // namespace k3::tok3n
