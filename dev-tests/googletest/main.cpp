#include <gtest/gtest.h>
#include <k3/tok3n.h>
#include <format>

using namespace k3::tok3n::operators;

auto digit = "0123456789"_any_of;
auto year = exactly<4>(digit) % join;
auto month = exactly<2>(digit) % join;
auto day = digit % exactly<2> % join;

auto parser = year >> "-"_ign >> month >> "-"_ign >> day;

//TEST(ISO8601, parse_result)
//{
//	auto result = parser.parse("2024-01-01");
//
//	ASSERT_TRUE(result.has_value());
//	EXPECT_EQ(*result, std::tuple("2024", "01", "01"));
//}

TEST(ISO8601, parse_result)
{
	std::string_view input = "2024-01-01";
	auto result = parser.parse(input);

	ASSERT_TRUE(result.has_value())
		<< std::format("Input could not be parsed.\nInput = \"{}\"\n"
		"Parser = {}", input, k3::tok3n::pretty(parser).view());
	EXPECT_EQ(*result, std::tuple("2024", "01", "01"));
}

TEST(ISO8601, combinator_result)
{
	//static_assert(std::same_as<decltype(month), decltype(year)>);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
