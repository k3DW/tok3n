#pragma once
#include <tok3n/parsers/basic/OneChar.h>
#include <tok3n/parsers/basic/NotChar.h>
#include <tok3n/parsers/basic/Literal.h>
#include <tok3n/parsers/adaptor/Ignore.h>

TOK3N_BEGIN_NAMESPACE(inline operators)

template <StaticString str>
requires detail::SingleChar_able<str>
constexpr auto one = OneChar<str>{};

template <StaticString str>
requires detail::SingleChar_able<str>
constexpr auto not_ = NotChar<str>{};

template <StaticString str>
requires detail::Literal_able<str>
constexpr auto lit = Literal<str>{};

template <StaticString str>
requires detail::Literal_able<str>
constexpr auto ign = Ignore<Literal<str>>{};



template <StaticString str>
requires detail::SingleChar_able<str>
consteval auto operator"" _one()
{
	return one<str>;
}

template <StaticString str>
requires detail::SingleChar_able<str>
consteval auto operator"" _not()
{
	return not_<str>;
}

template <StaticString str>
requires detail::Literal_able<str>
consteval auto operator"" _lit()
{
	return lit<str>;
}

template <StaticString str>
requires detail::Literal_able<str>
consteval auto operator"" _ign()
{
	return ign<str>;
}

TOK3N_END_NAMESPACE(inline operators)
