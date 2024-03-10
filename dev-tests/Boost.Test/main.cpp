#define BOOST_TEST_MODULE MyTest
//#define BOOST_TEST_NO_MAIN 
#include <boost/test/included/unit_test.hpp>

#include <k3/tok3n.h>
#include <iostream>

auto pp = k3::tok3n::any<"123"> >> k3::tok3n::any<"abc">;

namespace k3::tok3n
{
    std::ostream& operator<<(std::ostream& os, ParserFamily family)
    {
        return os << "ParserFamily(" << (int)family << ")";
    }
}

namespace std
{

    template <class... Ts>
    ostream& operator<<(ostream& os, const tuple<Ts...> tup)
    {
        os << "[";
        if constexpr (sizeof...(Ts) >= 1)
            os << get<0>(tup);
        [&]<size_t... Is>(index_sequence<Is...>)
        {
            ((os << ", " << get<Is + 1>(tup)), ...);
        }(make_index_sequence<sizeof...(Ts) - 1>{});
        return os << "]";
    }

}

BOOST_AUTO_TEST_CASE(first_test)
{
  BOOST_TEST(pp.family == k3::tok3n::ParserFamily::Sequence);
  BOOST_TEST(pp.parse("1a").has_value());
  BOOST_TEST(*pp.parse("1a") == std::tuple("1", "a"));
}

// int main(int argc, char* argv[])
// {
//     int exitCode = ::boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
//     return exitCode;
// }
