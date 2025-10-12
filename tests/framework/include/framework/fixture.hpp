// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_FIXTURE_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_FIXTURE_HPP

#include <iosfwd>
#include <string>
#include <string_view>
#include <unordered_map>
#include "framework/hash.hpp"
#include "framework/test.hpp"

namespace k3::testing {

struct fixture_result;

class fixture
{
public:
    void add_test(test&& t);

    std::string_view name() const
    {
        return _name;
    }

    fixture_result run(std::ostream& os) const;
    fixture_result run(std::ostream& os, std::string_view test_name) const;

    void list(std::ostream& os) const;

protected:
    fixture(std::string name)
        : _name(std::move(name))
    {}

    template <std::size_t hash>
    static fixture& global(std::string name) {
        static fixture f(std::move(name));
        return f;
    }

private:
    std::string _name;
    std::unordered_map<std::string_view, test> _tests;
};

} // namespace k3::testing



#define FIXTURE(NAME)                                                                     \
    template <std::size_t hash>                                                           \
    class fixture_impl_;                                                                  \
    template <>                                                                           \
    class fixture_impl_<::k3::testing::simple_hash(NAME)>                                 \
        : private ::k3::testing::fixture                                                  \
    {                                                                                     \
    private:                                                                              \
        static inline bool _init = ::k3::testing::runner::get()                           \
            .add(::k3::testing::fixture::global<::k3::testing::simple_hash(NAME)>(NAME)); \
    }

#endif // K3_TOK3N_TESTS_FRAMEWORK_FIXTURE_HPP
