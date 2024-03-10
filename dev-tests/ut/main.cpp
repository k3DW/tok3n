#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp> // import boost.ut;

constexpr auto sum(auto... values) { return (values + ...); }

int main() {
  using namespace boost::ut;

  "sum"_test = [] {
    expect(sum(0) == 0_i);
    expect(sum(1, 2) == 3_i);
    expect(sum(1, 2) > 0_i and 41_i == sum(40, 2));
  };
}
