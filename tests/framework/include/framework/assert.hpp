// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_ASSERT_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_ASSERT_HPP

// The template argument `[&]{ return bool(CONDITION); }()` is a workaround for Clang 16

#define ASSERT_COMPILE_TIME(CONDITION, MESSAGE)                                                                            \
    if (                                                                                                                   \
        bool _ct = ::k3::testing::test_result_context::check(std::bool_constant<[&]{ return bool(CONDITION); }()>::value); \
        not _ct                                                                                                            \
    )                                                                                                                      \
        return ::k3::testing::test_result_context::add_error(_ct, true, MESSAGE, Error::Fatality::fatal)

#define ASSERT_RUN_TIME(CONDITION, MESSAGE)                                                              \
    if (                                                                                                 \
        bool _rt = ::k3::testing::test_result_context::check(CONDITION);                                 \
        not _rt                                                                                          \
    )                                                                                                    \
        return ::k3::testing::test_result_context::add_error(true, _rt, MESSAGE, Error::Fatality::fatal)

#define ASSERT_COMPILE_AND_RUN_TIME(CONDITION, MESSAGE)                                                                    \
    if (                                                                                                                   \
        bool _ct = ::k3::testing::test_result_context::check(std::bool_constant<[&]{ return bool(CONDITION); }()>::value), \
             _rt = ::k3::testing::test_result_context::check(CONDITION);                                                   \
        not _ct or not _rt                                                                                                 \
    )                                                                                                                      \
        return ::k3::testing::test_result_context::add_error(_ct, _rt, MESSAGE, Error::Fatality::fatal)

#define EXPECT_COMPILE_TIME(CONDITION, MESSAGE)                                                                            \
    if (                                                                                                                   \
        bool _ct = ::k3::testing::test_result_context::check(std::bool_constant<[&]{ return bool(CONDITION); }()>::value); \
        not _ct                                                                                                            \
    )                                                                                                                      \
        ::k3::testing::test_result_context::add_error(_ct, true, MESSAGE, Error::Fatality::non_fatal)

#define EXPECT_RUN_TIME(CONDITION, MESSAGE)                                                           \
    if (                                                                                              \
        bool _rt = ::k3::testing::test_result_context::check(CONDITION);                              \
        not _rt                                                                                       \
    )                                                                                                 \
        ::k3::testing::test_result_context::add_error(true, _rt, MESSAGE, Error::Fatality::non_fatal)

#define EXPECT_COMPILE_AND_RUN_TIME(CONDITION, MESSAGE)                                                                    \
    if (                                                                                                                   \
        bool _ct = ::k3::testing::test_result_context::check(std::bool_constant<[&]{ return bool(CONDITION); }()>::value), \
             _rt = ::k3::testing::test_result_context::check(CONDITION);                                                   \
        not _ct or not _rt                                                                                                 \
    )                                                                                                                      \
        ::k3::testing::test_result_context::add_error(_ct, _rt, MESSAGE, Error::Fatality::non_fatal)



#define ASSERT(CONDITION, MESSAGE) \
    ASSERT_COMPILE_AND_RUN_TIME(CONDITION, MESSAGE)

#define EXPECT(CONDITION, MESSAGE) \
    EXPECT_COMPILE_AND_RUN_TIME(CONDITION, MESSAGE)

#define SIMPLE_EXPECT(CONDITION) \
    EXPECT(CONDITION, #CONDITION)



#define IDENTITY(...) __VA_ARGS__

#define STR(...) #__VA_ARGS__

#endif // K3_TOK3N_TESTS_FRAMEWORK_ASSERT_HPP
