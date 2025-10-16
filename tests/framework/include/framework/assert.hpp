// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_ASSERT_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_ASSERT_HPP

#if defined(__clang__) and (__clang_major__ <= 16)
#define K3_TOK3N_CT_BOOL_(B) ([&]{ return bool(B); }())
#else
#define K3_TOK3N_CT_BOOL_(B) (bool(B))
#endif

#define K3_TOK3N_CHECK_CT_(CONDITION) \
    (::k3::testing::context::check(std::bool_constant<K3_TOK3N_CT_BOOL_(CONDITION)>::value))
#define K3_TOK3N_CHECK_RT_(CONDITION) \
    (::k3::testing::context::check(CONDITION))
#define K3_TOK3N_FATAL_ERROR_(CT, RT) \
    return ::k3::testing::void_assignment_helper{} = ::k3::testing::context::add_error(CT, RT, ::k3::testing::error_fatality::fatal)
#define K3_TOK3N_NON_FATAL_ERROR_(CT, RT) \
    ::k3::testing::void_assignment_helper{} = ::k3::testing::context::add_error(CT, RT, ::k3::testing::error_fatality::non_fatal)

#define ASSERT_COMPILE_TIME(CONDITION)            \
    if (                                          \
        bool _ct = K3_TOK3N_CHECK_CT_(CONDITION); \
        not _ct                                   \
    )                                             \
        K3_TOK3N_FATAL_ERROR_(_ct, true)

#define ASSERT_RUN_TIME(CONDITION)                \
    if (                                          \
        bool _rt = K3_TOK3N_CHECK_RT_(CONDITION); \
        not _rt                                   \
    )                                             \
        K3_TOK3N_FATAL_ERROR_(true, _rt)

#define ASSERT_COMPILE_AND_RUN_TIME(CONDITION)    \
    if (                                          \
        bool _ct = K3_TOK3N_CHECK_CT_(CONDITION), \
             _rt = K3_TOK3N_CHECK_RT_(CONDITION); \
        not _ct or not _rt                        \
    )                                             \
        K3_TOK3N_FATAL_ERROR_(_ct, _rt)

#define EXPECT_COMPILE_TIME(CONDITION)            \
    if (                                          \
        bool _ct = K3_TOK3N_CHECK_CT_(CONDITION); \
        not _ct                                   \
    )                                             \
        K3_TOK3N_NON_FATAL_ERROR_(_ct, true)

#define EXPECT_RUN_TIME(CONDITION)                \
    if (                                          \
        bool _rt = K3_TOK3N_CHECK_RT_(CONDITION); \
        not _rt                                   \
    )                                             \
        K3_TOK3N_NON_FATAL_ERROR_(true, _rt)

#define EXPECT_COMPILE_AND_RUN_TIME(CONDITION)    \
    if (                                          \
        bool _ct = K3_TOK3N_CHECK_CT_(CONDITION), \
             _rt = K3_TOK3N_CHECK_RT_(CONDITION); \
        not _ct or not _rt                        \
    )                                             \
        K3_TOK3N_NON_FATAL_ERROR_(_ct, _rt)



#define ASSERT(CONDITION) \
    ASSERT_COMPILE_AND_RUN_TIME(CONDITION)

#define EXPECT(CONDITION) \
    EXPECT_COMPILE_AND_RUN_TIME(CONDITION)

#define SIMPLE_EXPECT(CONDITION) \
    EXPECT(CONDITION) << #CONDITION



#define IDENTITY(...) __VA_ARGS__

#define STR(...) #__VA_ARGS__

#endif // K3_TOK3N_TESTS_FRAMEWORK_ASSERT_HPP
