#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <vector>

namespace k3::tok3n {

template <class P>
concept MaybeConstructible =
	Parser<P> and
	not std::same_as<typename P::result_type, void>;

template <class P, class N>
concept ExactlyConstructible =
	Parser<P> and
	IsConst<N, std::size_t> and
	(N::value != 0) and
	not std::same_as<typename P::result_type, void>;

template <class P>
concept OneOrMoreConstructible =
	Parser<P> and
	not std::same_as<typename P::result_type, void>;

template <class P>
concept ZeroOrMoreConstructible =
	Parser<P> and
	not std::same_as<typename P::result_type, void>;

template <class P, class D, class KeepDelimiters>
concept DelimitConstructible =
	Parser<P> and
	Parser<D> and
	ParserCompatibleWith<P, D> and
	IsConst<KeepDelimiters, bool> and
	not std::same_as<typename P::result_type, void> and
	((not KeepDelimiters::value) or (KeepDelimiters::value and not std::same_as<typename D::result_type, void>));



template <Parser P>
requires MaybeConstructible<P>
struct Maybe;

template <Parser P, IsConst<std::size_t> N>
requires ExactlyConstructible<P, N>
struct Exactly;

template <Parser P>
requires OneOrMoreConstructible<P>
struct OneOrMore;

template <Parser P>
requires ZeroOrMoreConstructible<P>
struct ZeroOrMore;

template <Parser P, Parser D, IsConst<bool> KeepDelimiters>
requires DelimitConstructible<P, D, KeepDelimiters>
struct Delimit;

} // namespace k3::tok3n
