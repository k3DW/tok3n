#pragma once
#include <k3/tok3n/concepts/Parser.h>
#include <k3/tok3n/types/StaticString.h>

using namespace k3::tok3n;

struct underlying
{
private:
	template <template <class> class ParserTemplate, Parser P>
	static consteval auto impl(ParserTemplate<P>) { return P{}; }

	template <template <StaticString> class ParserTemplate, StaticString str>
	static consteval auto impl(ParserTemplate<str>) { return str; }

public:
	template <Parser P>
	using parser = decltype(impl(P{}));

	template <Parser P>
	static constexpr auto string = impl(P{});
};
