// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_TEST_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_TEST_HPP

#include <iosfwd>
#include <string>
#include <string_view>
#include "framework/hash.hpp"

namespace k3::testing {

struct test_result;

class test
{
public:
    std::string_view name() const
    {
        return _name;
    }

    test_result run(std::ostream& os) const;

    using func_type = void(*)();

    template <std::size_t N>
    test(const char(&name)[N], func_type func)
        : _name(name), _func(func) {}

private:
    std::string_view _name; // This is fine because we only construct with a string literal
    func_type _func;
};

} // namespace k3::testing



#define TEST(FIXTURE_NAME, NAME)                                                      \
    template <std::size_t hash>                                                       \
    class test_impl_;                                                                 \
    template <std::size_t hash>                                                       \
    class fixture_impl_;                                                              \
    template <>                                                                       \
    class test_impl_<::k3::testing::simple_hash(FIXTURE_NAME, NAME)>                  \
    {                                                                                 \
    private:                                                                          \
        static_assert(                                                                \
            std::is_base_of_v<::k3::testing::fixture,                                 \
                fixture_impl_<::k3::testing::simple_hash(FIXTURE_NAME)>>,             \
            "Fixture \"" FIXTURE_NAME "\" has not been declared in this namespace."); \
        static void _run();                                                           \
        static inline const bool _init = ::k3::testing::runner::get()                 \
            .add(FIXTURE_NAME, ::k3::testing::test(NAME, &_run));                     \
    };                                                                                \
    void test_impl_<::k3::testing::simple_hash(FIXTURE_NAME, NAME)>::_run()

#endif // K3_TOK3N_TESTS_FRAMEWORK_TEST_HPP
