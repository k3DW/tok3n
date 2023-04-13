#include <tok3n/tok3n.h>
#include <iostream>
#include "examples/algebraic.h"

int main()
{
	using namespace k3;
	using namespace k3::tok3n;

	using namespace k3::tok3n::examples;

	constexpr auto oc = OneChar<"ab">{};
	constexpr auto test = exactly<2>(oc);

	[[maybe_unused]] auto algtest = algebraic::test();

	auto result_ = test.parse("cbac");
	auto result_2 = test.parse("abac");
}
