#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>

namespace k3::tok3n {

template <class... Ps>
concept ChoiceConstructible =
	(detail::parser<Ps> and ...) and
	(sizeof...(Ps) >= 2) and
	detail::all_same<typename Ps::value_type...>;

template <class... Ps>
concept SequenceConstructible =
	(detail::parser<Ps> and ...) and
	(sizeof...(Ps) >= 2) and
	detail::all_same<typename Ps::value_type...>;



template <detail::parser... Ps>
requires ChoiceConstructible<Ps...>
struct Choice;

template <detail::parser... Ps>
requires SequenceConstructible<Ps...>
struct Sequence;

} // namespace k3::tok3n
