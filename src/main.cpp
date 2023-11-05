#include <k3/tok3n.h>
#include <iostream>

int main()
{
	using namespace k3;
	using namespace k3::tok3n;

	constexpr auto oc = AnyOf<"ab">{};
	constexpr auto test = exactly<2>(oc);

	auto result_ = test.parse("cbac");
	auto result_2 = test.parse("abac");
}
