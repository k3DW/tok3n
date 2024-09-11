#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <k3/tok3n/detail/parser.h>

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



namespace detail
{

	template <class ResultType>
	struct ExecutorData
	{
		ResultType value = {};
	};

	template <>
	struct ExecutorData<void>
	{
	};

} // namespace detail

} // namespace k3::tok3n
