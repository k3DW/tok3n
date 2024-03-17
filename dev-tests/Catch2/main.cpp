
// #define CATCH_CONFIG_RUNTIME_STATIC_REQUIRE
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <k3/tok3n.h>
#include <format>
#include <iostream>

using namespace k3::tok3n::operators;

auto digit = "0123456789"_any_of;
auto year = exactly<4>(digit) % join;
auto month = exactly<2>(digit) % join;
auto day = digit % exactly<2> % join;

auto parser = year >> "-"_ign >> month >> "-"_ign >> day;

using Digit   = decltype(digit);
using Year    = decltype(year);
using Month   = decltype(month);
using Day     = decltype(day);
using ISODate = decltype(parser);

using k3::tok3n::Parser;
using k3::tok3n::ParserFamily;

//template <k3::tok3n::Parser P>
//requires requires { k3::tok3n::pretty(P{}); }
//std::ostream& operator<<(std::ostream& os, P)
//{
//    return os << k3::tok3n::pretty(P{}).view();
//}
//
//namespace std
//{
//
//    template <class... Ts>
//    ostream& operator<<(ostream& os, const tuple<Ts...> tup)
//    {
//        os << "[";
//        if constexpr (sizeof...(Ts) >= 1)
//            os << get<0>(tup);
//        [&]<size_t... Is>(index_sequence<Is...>)
//        {
//            ((os << ", " << get<Is + 1>(tup)), ...);
//        }(make_index_sequence<sizeof...(Ts) - 1>{});
//        return os << "]";
//    }
//
//}

#if 0
TEST_CASE("ISO8601")
{
    std::string_view input = "2024-01-01";
	auto result = parser.parse(input);

	REQUIRE(result.has_value());
	CHECK(*result == std::tuple("2024", "01", "01"));
}
//#else
TEST_CASE("ISO8601")
{
    std::string_view input = "bad";
    auto result = parser.parse(input);

    INFO(std::format("Input could not be parsed.\nInput = \"{}\"\n"
        "Parser = {}", input, k3::tok3n::pretty(parser).view()));

    REQUIRE(result.has_value());
    CHECK(*result == std::tuple("2024", "01", "01"));
}
#endif

//#define ASSERT_PARSE_SUCCESS(P, INPUT, RESULT) \
//  STATIC_REQUIRE(P::parse(INPUT).has_value()); \
//  STATIC_CHECK(*P::parse(INPUT) == (RESULT))

#define ASSERT_PARSE_SUCCESS(P, INPUT, RESULT)    \
  [](auto)                                        \
  {                                               \
    STATIC_REQUIRE(P::parse(INPUT).has_value());  \
    if constexpr (P::parse(INPUT).has_value())    \
    {                                             \
      STATIC_CHECK(*P::parse(INPUT) == (RESULT)); \
    }                                             \
    else                                          \
    {                                             \
      CHECK(*P::parse(INPUT) == (RESULT));        \
    }                                             \
  }(int{})

//TEST_CASE("ISO8601 properties")
//{
//    STATIC_REQUIRE(Parser<ISODate>);
//    STATIC_REQUIRE(ISODate::family == ParserFamily::Sequence);
//    //STATIC_REQUIRE(ParserFor<ISODate, char>);
//}

TEST_CASE("ISO8601 parsing")
{
    //STATIC_REQUIRE(ISODate::parse("2024-01-01").has_value());
    //STATIC_CHECK(*ISODate::parse("2024-01-01") == std::tuple("2024", "01", "01"));


    ASSERT_PARSE_SUCCESS(ISODate, "bad", std::tuple("b", "a", "d"));

    //ASSERT_PARSE_SUCCESS(ISODate, "2024-01-01", std::tuple("2024", "01", "01"));
}

int main( int argc, char* argv[] )
{
    // your setup ...

    int result = Catch::Session().run( argc, argv );

    // your clean-up...

    return result;
}
