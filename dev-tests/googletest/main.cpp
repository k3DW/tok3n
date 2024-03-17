#include <gtest/gtest.h>
#include <k3/tok3n.h>
#include <format>

using namespace k3::tok3n::operators;

auto digit = "0123456789"_any_of;
auto year = exactly<4>(digit) % join;
auto month = exactly<2>(digit) % join;
auto day = digit % exactly<2> % join;

auto parser = year >> "-"_ign >> month >> "-"_ign >> day;

using Digit  = decltype(digit);
using Year   = decltype(year);
using Month  = decltype(month);
using Day    = decltype(day);
using ISODate = decltype(parser);

//TEST(ISO8601, parse_result)
//{
//	auto result = parser.parse("2024-01-01");
//
//	ASSERT_TRUE(result.has_value());
//	EXPECT_EQ(*result, std::tuple("2024", "01", "01"));
//}

//using k3::tok3n::ParserFor;
using k3::tok3n::Output;


#define ASSERT_PARSE_SUCCESS(P, INPUT, RESULT) \
  static_assert(P::parse(INPUT).has_value());  \
  ASSERT_TRUE(P::parse(INPUT).has_value());    \
  static_assert(*P::parse(INPUT) == (RESULT)); \
  EXPECT_EQ(*P::parse(INPUT), (RESULT))

TEST(ISO8601, properties)
{
	static_assert(std::same_as<Month, Day>);
	static_assert(!std::same_as<Year, Day>);
	
	//static_assert(ParserFor<ISODate, char>);
	//static_assert(std::same_as<ISODate::result_for<char>,
	//              std::tuple<Output<char>, Output<char>, Output<char>>>);
	
	static_assert(ISODate::parse("2024-01-01").has_value());
	static_assert(*ISODate::parse("2024-01-01")
		== std::tuple("2024", "01", "01"));
	static_assert(!ISODate::parse("bad").has_value());
}

TEST(ISO8601, full_date)
{
	//ASSERT_PARSE_SUCCESS(ISODate, "bad", std::tuple("b", "a", "d"));

	ASSERT_PARSE_SUCCESS(ISODate, "2024-01-01", std::tuple("2024", "01", "01"));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
