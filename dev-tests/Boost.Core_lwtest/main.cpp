#define BOOST_TEST_MODULE TestModule
//#define BOOST_TEST_NO_MAIN
#include <boost/core/lightweight_test.hpp>

#include <k3/tok3n.h>
#include <format>

using namespace k3::tok3n;

auto digit = "0123456789"_any_of;
auto year = exactly<4>(digit) % join;
auto month = exactly<2>(digit) % join;
auto day = digit % exactly<2> % join;

// ISO-8601 YYYY-MM-DD
auto parser = year >> "-"_ign >>
			  month >> "-"_ign >> day;

//namespace std
//{
//
//    template <class... Ts>
//    std::ostream& operator<<(std::ostream& os, const std::tuple<Ts...> tup)
//    {
//        os << "[";
//        if constexpr (sizeof...(Ts) >= 1)
//            os << std::get<0>(tup);
//        [&] <std::size_t... Is>(std::index_sequence<Is...>)
//        {
//            ((os << ", " << std::get<Is + 1>(tup)), ...);
//        }(std::make_index_sequence<sizeof...(Ts) - 1>{});
//        return os << "]";
//    }
//
//}

//BOOST_AUTO_TEST_CASE(ISO8601)
//{
//    auto result = parser.parse("bad");
//
//    BOOST_REQUIRE(result.has_value());
//    BOOST_CHECK((*result == std::tuple("2024", "01", "01")));
//}

#if 1
void ISO8601()
{
    std::string_view input = "bad";
    auto result = parser.parse(input);

    if (!BOOST_TEST(result.has_value()))
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM <<
            std::format("Input could not be parsed.\nInput = \"{}\"\n"
            "Parser = {}\n", input, k3::tok3n::pretty(parser).view());
        return;
    }
    BOOST_TEST(*result == std::tuple("2024", "01", "01"));
}
#else
void ISO8601()
{
    std::string_view input = "2024-01-01";
    auto result = parser.parse(input);

    BOOST_TEST(result.has_value());
    BOOST_TEST(*result == std::tuple("2024", "01", "01"));
}
#endif

int main()
{
    ISO8601();
    return boost::report_errors();
}
