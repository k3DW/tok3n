#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp> // import boost.ut;
#include <k3/tok3n.h>
#include <format>

namespace k3
{
	
using namespace k3::tok3n::operators;

auto digit = "0123456789"_any_of;
auto year = exactly<4>(digit) % join;
auto month = exactly<2>(digit) % join;
auto day = digit % exactly<2> % join;

auto parser = year >> "-"_ign >> month >> "-"_ign >> day;

}

using Digit   = decltype(k3::digit);
using Year    = decltype(k3::year);
using Month   = decltype(k3::month);
using Day     = decltype(k3::day);
using ISODate = decltype(k3::parser);


using k3::tok3n::Parser;
using k3::tok3n::ParserFamily;


//#define ASSERT_PARSE_SUCCESS(P, INPUT, RESULT)    \
//  expect(constant<P::parse(INPUT).has_value()>);  \
//  expect(P::parse(INPUT).has_value());            \
//  expect(constant<*P::parse(INPUT) == (RESULT)>); \
//  expect(*P::parse(INPUT) == (RESULT))

#if 0
#define ASSERT_PARSE_SUCCESS(P, INPUT, RESULT)      \
  expect(constant<P::parse(INPUT).has_value()>);    \
  expect(P::parse(INPUT).has_value()) << fatal;     \
  if constexpr (P::parse(INPUT).has_value())  {     \
    expect(constant<*P::parse(INPUT) == (RESULT)>); \
  }                                                 \
  expect(*P::parse(INPUT) == (RESULT))
#endif

#define EXPECT_CT_AND_RT_FATAL(COND, MESSAGE)     \
  expect(constant<(COND)>) << (MESSAGE) << fatal; \
  expect(COND) << (MESSAGE) << fatal

#define EXPECT_CT_AND_RT_NONFATAL(COND) \
  expect(constant<(COND)>);             \
  expect(COND)

#define ASSERT_PARSE_SUCCESS(P, INPUT, RESULT)                 \
  EXPECT_CT_AND_RT_FATAL(P::parse(INPUT).has_value(),          \
    std::format("Input could not be parsed.\nInput = \"{}\"\n" \
    "Parser = {}", (INPUT), k3::tok3n::pretty(P{}).view()));   \
  if constexpr (P::parse(INPUT).has_value()) {                 \
    EXPECT_CT_AND_RT_NONFATAL(*P::parse(INPUT) == (RESULT));   \
  }

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
//#else
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



	
	//"ISO8601 properties"_test = []
	//{
	//	expect(constant<Parser<ISODate>>);
	//	expect(constant<ISODate::family == ParserFamily::Sequence>);
	//	//expect(constant<ParserFor<ISODate, char>>);
	//};

	"ISO8601 parsing"_test = []
	{
		//ASSERT_PARSE_SUCCESS(ISODate, "2024-01-01", std::tuple("2024", "01", "02"));
		ASSERT_PARSE_SUCCESS(ISODate, "bad", std::tuple("b", "a", "d"));
	};

}
