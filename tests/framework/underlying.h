#pragma once
#include <k3/tok3n/concepts/Parser.h>
#include <k3/tok3n/types/StaticString.h>

struct underlying
{
private:
	template <template <class> class ParserTemplate, k3::tok3n::Parser P>
	static consteval auto impl(ParserTemplate<P>) { return P{}; }

	template <template <k3::tok3n::StaticString> class ParserTemplate, k3::tok3n::StaticString str>
	static consteval auto impl(ParserTemplate<str>) { return str; }

public:
	template <k3::tok3n::Parser P>
	using parser = decltype(impl(P{}));

	template <k3::tok3n::Parser P>
	static constexpr auto string = impl(P{});
};
