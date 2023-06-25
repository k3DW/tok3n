#pragma once
#include <k3/tok3n/concepts/Parser.h>
#include <k3/tok3n/concepts/is_bool_constant.h>

namespace k3::tok3n::constructible {

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

template <class P, class D, class KeepDelimiters>
concept Delimit =
	Parser<P> and
	Parser<D> and
	is_bool_constant<KeepDelimiters> and
	not std::same_as<typename P::result_type, void> and
	((not KeepDelimiters::value) or (KeepDelimiters::value and not std::same_as<typename D::result_type, void>));

} // namespace k3::tok3n::constructible
