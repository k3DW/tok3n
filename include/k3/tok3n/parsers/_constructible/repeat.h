#pragma once
#include <k3/tok3n/concepts/Parser.h>

TOK3N_BEGIN_NAMESPACE(constructible)

template <class P>
concept Maybe =
	Parser<P> and
	not std::same_as<typename P::result_type, void>;

template <class P, std::size_t N>
concept Exactly =
	Parser<P> and
	(N != 0) and
	not std::same_as<typename P::result_type, void>;

template <class P>
concept OneOrMore =
	Parser<P> and
	not std::same_as<typename P::result_type, void>;

template <class P>
concept ZeroOrMore =
	Parser<P> and
	not std::same_as<typename P::result_type, void>;

template <class P, class D, bool ShouldKeep>
concept Delimit =
	Parser<P> and
	Parser<D> and
	not std::same_as<typename P::result_type, void> and
	((not ShouldKeep) or (ShouldKeep and not std::same_as<typename D::result_type, void>));

TOK3N_END_NAMESPACE(constructible)
