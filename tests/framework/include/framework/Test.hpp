// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_TEST_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_TEST_HPP

#include <iosfwd>
#include <string>
#include <string_view>
#include "framework/Hash.hpp"

struct TestResult;

class Test
{
public:
    std::string_view name() const
    {
        return _name;
    }

    TestResult run(std::ostream& os) const;

    using func_type = void(*)();

    template <std::size_t N>
    Test(const char(&name)[N], func_type func)
        : _name(name), _func(func) {}

private:
    std::string_view _name; // This is fine because we only construct with a string literal
    func_type _func;
};



#define TEST(FIXTURE_NAME, NAME)                                                      \
    template <std::size_t hash>                                                       \
    class TestImpl;                                                                   \
    template <>                                                                       \
    class TestImpl<test_hash(FIXTURE_NAME, NAME)>                                     \
    {                                                                                 \
    private:                                                                          \
        static_assert(                                                                \
            std::is_base_of_v<::Fixture, FixtureImpl<test_hash(FIXTURE_NAME)>>,       \
            "Fixture \"" FIXTURE_NAME "\" has not been declared in this namespace."); \
        static void _run();                                                           \
        static inline const bool _init                                                \
            = Runner::get().add(FIXTURE_NAME, Test(NAME, &_run));                     \
    };                                                                                \
    void TestImpl<test_hash(FIXTURE_NAME, NAME)>::_run()

#endif // K3_TOK3N_TESTS_FRAMEWORK_TEST_HPP
