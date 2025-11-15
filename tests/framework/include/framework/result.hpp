// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_TESTRESULT_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_TESTRESULT_HPP

#include <iosfwd>
#include <ostream>
#include <source_location>
#include <sstream>
#include <string_view>
#include <string>
#include <vector>

namespace k3::testing {

struct error;

struct test_result
{
    test_result(std::string_view name_)
        : name(name_) {}

    std::string_view name;
    std::size_t checks = 0;
    std::vector<error> errors{};

    void print_brief(std::ostream& os) const;
    void print_errors(std::ostream& os) const;
};

struct fixture_result
{
    fixture_result(std::string_view name_)
        : name(name_) {}

    std::string_view name;
    std::vector<test_result> passes;
    std::vector<test_result> failures;

    void push_back(test_result&& result);
    void print_brief(std::ostream& os) const;
    void print_errors(std::ostream& os) const;
};

struct check_result
{
    bool compile_time;
    bool run_time;
    operator bool() const noexcept
    {
        return compile_time and run_time;
    }
};

class void_assignment_helper
{
public:
    void_assignment_helper() = default;
    void operator=(auto&&) const {}
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

    class trace_context : public context_base
    {
    public:
        [[nodiscard]] trace_context(std::source_location location = std::source_location::current())
        {
            _trace.push_back(std::move(location));
        }
        ~trace_context()
        {
            _trace.pop_back();
        }
    };

    class message_streaming_context : public context_base
    {
    public:
        message_streaming_context(std::string& message)
            : _message(&message)
        {}
        ~message_streaming_context()
        {
            *_message = std::move(_stream).str();
        }
        template <class T>
        friend message_streaming_context&& operator<<(message_streaming_context&& ctx, T&& value)
        {
            ctx._stream << std::forward<T>(value);
            return std::move(ctx);
        }
    private:
        std::ostringstream _stream;
        std::string* _message;
    };

    static message_streaming_context add_error(check_result result, error_fatality fatality, std::source_location location = std::source_location::current());

    static check_result check(bool compile_time, bool run_time);

    static std::size_t total_errors();

private:
    static inline test_result* _current_result = nullptr;
    static inline std::vector<std::source_location> _trace;

    static inline std::size_t _total_errors = 0;
};

} // namespace k3::testing

#endif // K3_TOK3N_TESTS_FRAMEWORK_TESTRESULT_HPP
