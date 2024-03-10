#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp> // import boost.ut;
#include <k3/tok3n.h>
#include <format>

using namespace k3::tok3n::operators;

auto digit = "0123456789"_any_of;
auto year = exactly<4>(digit) % join;
auto month = exactly<2>(digit) % join;
auto day = digit % exactly<2> % join;

auto parser = year >> "-"_ign >> month >> "-"_ign >> day;

int main()
{
	using namespace boost::ut;

#if 0
	"ISO8601"_test = []
	{
		std::string_view input = "2024-01-01";
		auto result = parser.parse(input);

		expect(fatal(result.has_value()));
		expect(*result == std::tuple("2024", "01", "01"));
	};
#else
	"ISO8601"_test = []
	{
		std::string_view input = "bad";
		auto result = parser.parse(input);

		expect(result.has_value())
			<< std::format("Input could not be parsed.\nInput = \"{}\"\n"
			   "Parser = {}", input, k3::tok3n::pretty(parser).view())
			<< fatal;
		expect(*result == std::tuple("2024", "01", "01"));
	};
#endif
}
