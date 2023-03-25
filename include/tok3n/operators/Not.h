#pragma once
#include <tok3n/parsers/basic/OneChar.h>
#include <tok3n/parsers/basic/NotChar.h>

TOK3N_BEGIN_NAMESPACE()

inline namespace operators
{

template <StaticString str>
constexpr auto operator!(OneChar<str>)
{
	return NotChar<str>{};
}
template <StaticString str>
constexpr auto operator!(NotChar<str>)
{
	return OneChar<str>{};
}

}

TOK3N_END_NAMESPACE()
