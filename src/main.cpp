#include <k3/tok3n.h>
#include <iostream>

int main()
{
	using namespace k3;
	using namespace k3::tok3n;

	constexpr auto oc = detail::any_of_parser<"ab">{};
	constexpr auto test = exactly<2>(oc);

	[[maybe_unused]] auto result_ = test.parse("cbac");
	[[maybe_unused]] auto result_2 = test.parse("abac");
}
