#pragma once
#include <k3/tok3n/concepts/Parser.h>
#include <k3/tok3n/meta/all_same.h>

TOK3N_BEGIN_NAMESPACE(constructible)

template <class... Ps>
concept Choice =
	(Parser<Ps> and ...) and
	(sizeof...(Ps) >= 2) and
	meta::all_same<typename Ps::result_type...>;

template <class... Ps>
concept Sequence =
	(Parser<Ps> and ...) and
	(sizeof...(Ps) >= 2);

TOK3N_END_NAMESPACE(constructible)
