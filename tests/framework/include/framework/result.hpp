// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_TESTRESULT_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_TESTRESULT_HPP

#include <iosfwd>
#include <string_view>
#include <vector>

namespace k3::testing {

struct error;

struct test_result
{
    test_result(std::string_view name)
        : name(name) {}

    std::string_view name;
    std::size_t checks = 0;
    std::vector<error> errors{};

    void print_brief(std::ostream& os) const;
    void print_errors(std::ostream& os) const;
};

struct fixture_result
{
    fixture_result(std::string_view name)
        : name(name) {}

    std::string_view name;
    std::vector<test_result> passes;
    std::vector<test_result> failures;

    void push_back(test_result&& result);
    void print_brief(std::ostream& os) const;
    void print_errors(std::ostream& os) const;
};

class context
{
    class context_base
    {
    public:
        context_base() = default;
        context_base(const context_base&) = delete;
        context_base(context_base&&) = delete;
        context_base& operator=(const context_base&) = delete;
        context_base& operator=(context_base&&) = delete;
    };

public:
    class test_result_context : public context_base
    {
    public:
        [[nodiscard]] test_result_context(test_result& result);
        ~test_result_context();
    };

    static void add_error(bool ct, bool rt, std::string message, error_fatality fatality, std::source_location location = std::source_location::current());

    static bool check(bool condition);

private:
    static inline test_result* _current_result = nullptr;
};

} // namespace k3::testing

#endif // K3_TOK3N_TESTS_FRAMEWORK_TESTRESULT_HPP
