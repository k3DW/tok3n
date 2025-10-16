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

#define K3_TOK3N_REQUIRE_SEMICOLON_ static_assert(true, "require semicolon")

#define K3_TOK3N_CHECK_CT_(CONDITION) \
    (::k3::testing::context::check(std::bool_constant<K3_TOK3N_CT_BOOL_(CONDITION)>::value))
#define K3_TOK3N_CHECK_RT_(CONDITION) \
    (::k3::testing::context::check(CONDITION))
#define K3_TOK3N_FATAL_ERROR_(CT, RT) \
    return ::k3::testing::void_assignment_helper{} = ::k3::testing::context::add_error(CT, RT, ::k3::testing::error_fatality::fatal)
#define K3_TOK3N_NON_FATAL_ERROR_(CT, RT) \
    ::k3::testing::void_assignment_helper{} = ::k3::testing::context::add_error(CT, RT, ::k3::testing::error_fatality::non_fatal)

#define ASSERT_COMPILE_TIME(CONDITION)            \
    switch(0) case 0: default:                    \
    if (                                          \
        bool _ct = K3_TOK3N_CHECK_CT_(CONDITION); \
        _ct                                       \
    )                                             \
        (void)0;                                  \
    else                                          \
        K3_TOK3N_FATAL_ERROR_(_ct, true)

#define ASSERT_RUN_TIME(CONDITION)                \
    switch(0) case 0: default:                    \
    if (                                          \
        bool _rt = K3_TOK3N_CHECK_RT_(CONDITION); \
        _rt                                       \
    )                                             \
        (void)0;                                  \
    else                                          \
        K3_TOK3N_FATAL_ERROR_(true, _rt)

#define ASSERT_COMPILE_AND_RUN_TIME(CONDITION)    \
    switch(0) case 0: default:                    \
    if (                                          \
        bool _ct = K3_TOK3N_CHECK_CT_(CONDITION), \
             _rt = K3_TOK3N_CHECK_RT_(CONDITION); \
        _ct and _rt                               \
    )                                             \
        (void)0;                                  \
    else                                          \
        K3_TOK3N_FATAL_ERROR_(_ct, _rt)

#define EXPECT_COMPILE_TIME(CONDITION)            \
    switch(0) case 0: default:                    \
    if (                                          \
        bool _ct = K3_TOK3N_CHECK_CT_(CONDITION); \
        _ct                                       \
    )                                             \
        (void)0;                                  \
    else                                          \
        K3_TOK3N_NON_FATAL_ERROR_(_ct, true)

#define EXPECT_RUN_TIME(CONDITION)                \
    switch(0) case 0: default:                    \
    if (                                          \
        bool _rt = K3_TOK3N_CHECK_RT_(CONDITION); \
        _rt                                       \
    )                                             \
        (void)0;                                  \
    else                                          \
        K3_TOK3N_NON_FATAL_ERROR_(true, _rt)

#define EXPECT_COMPILE_AND_RUN_TIME(CONDITION)    \
    switch(0) case 0: default:                    \
    if (                                          \
        bool _ct = K3_TOK3N_CHECK_CT_(CONDITION), \
             _rt = K3_TOK3N_CHECK_RT_(CONDITION); \
        _ct and _rt                               \
    )                                             \
        (void)0;                                  \
    else                                          \
        K3_TOK3N_NON_FATAL_ERROR_(_ct, _rt)



// ASSERT_THAT does not ignore its internal non-fatal errors,
// and treats them as fatal errors.
#define ASSERT_THAT(FRAGMENT)                                                  \
    {                                                                          \
        ::k3::testing::context::trace_context _ctx_;                           \
        const std::size_t _starting_ = ::k3::testing::context::total_errors(); \
        (FRAGMENT)();                                                          \
        const std::size_t _ending_ = ::k3::testing::context::total_errors();   \
        if (_ending_ != _starting_)                                            \
            return;                                                            \
    } K3_TOK3N_REQUIRE_SEMICOLON_

// EXPECT_THAT ignores all the internal non-fatal errors,
// but it cannot ignore the fatal errors.
#define EXPECT_THAT(FRAGMENT)                                                        \
    {                                                                                \
        ::k3::testing::context::trace_context _ctx_;                                 \
        const std::size_t _starting_ = ::k3::testing::context::total_fatal_errors(); \
        (FRAGMENT)();                                                                \
        const std::size_t _ending_ = ::k3::testing::context::total_fatal_errors();   \
        if (_ending_ != _starting_)                                                  \
            return;                                                                  \
    } K3_TOK3N_REQUIRE_SEMICOLON_



#define ASSERT(CONDITION) \
    ASSERT_COMPILE_AND_RUN_TIME(CONDITION)

#define EXPECT(CONDITION) \
    EXPECT_COMPILE_AND_RUN_TIME(CONDITION)

#define SIMPLE_EXPECT(CONDITION) \
    EXPECT(CONDITION) << #CONDITION



#define IDENTITY(...) __VA_ARGS__

#define STR(...) #__VA_ARGS__

#endif // K3_TOK3N_TESTS_FRAMEWORK_ASSERT_HPP
