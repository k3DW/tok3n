// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_ASSERT_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_ASSERT_HPP

#if defined(__clang__) and (__clang_major__ <= 16)
#define K3_TESTING_CT_BOOL_(B) ([&] { return bool{(B)}; }())
#else
#define K3_TESTING_CT_BOOL_(B) (bool{(B)})
#endif



#define K3_TESTING_EVAL_BOOL_(NAME, BOOL) \
    K3_TESTING_ ## NAME ## _ ## BOOL ## _

#define K3_TESTING_CT_CONDITION_0_(CONDITION) (true)
#define K3_TESTING_CT_CONDITION_1_(CONDITION) (std::bool_constant<K3_TESTING_CT_BOOL_(CONDITION)>::value)

#define K3_TESTING_RT_CONDITION_0_(CONDITION) (true)
#define K3_TESTING_RT_CONDITION_1_(CONDITION) (CONDITION)

#define K3_TESTING_ERROR_FATALITY_0_(RESULT) \
    ::k3::testing::void_assignment_helper{} = ::k3::testing::context::add_error(RESULT, ::k3::testing::error_fatality::non_fatal)
#define K3_TESTING_ERROR_FATALITY_1_(RESULT) \
    return ::k3::testing::void_assignment_helper{} = ::k3::testing::context::add_error(RESULT, ::k3::testing::error_fatality::fatal)



#define K3_TESTING_GENERIC_CHECK_IMPL_(CONDITION, MAKE_CT, MAKE_RT, MAKE_ERROR) \
    switch(0) case 0: default:                                                  \
    if (                                                                        \
        const auto _res_ = ::k3::testing::context::check(                       \
            MAKE_CT(CONDITION),                                                 \
            MAKE_RT(CONDITION)                                                  \
        );                                                                      \
        _res_                                                                   \
    )                                                                           \
        (void)0;                                                                \
    else                                                                        \
        MAKE_ERROR(_res_)

#define K3_TESTING_GENERIC_CHECK_(CONDITION, IS_CT, IS_RT, IS_FATAL) \
    K3_TESTING_GENERIC_CHECK_IMPL_(CONDITION,                        \
        K3_TESTING_EVAL_BOOL_(CT_CONDITION, IS_CT),                  \
        K3_TESTING_EVAL_BOOL_(RT_CONDITION, IS_RT),                  \
        K3_TESTING_EVAL_BOOL_(ERROR_FATALITY, IS_FATAL)              \
    )

#define ASSERT_COMPILE_TIME(CONDITION)         K3_TESTING_GENERIC_CHECK_(CONDITION, 1, 0, 1)
#define ASSERT_RUN_TIME(CONDITION)             K3_TESTING_GENERIC_CHECK_(CONDITION, 0, 1, 1)
#define ASSERT_COMPILE_AND_RUN_TIME(CONDITION) K3_TESTING_GENERIC_CHECK_(CONDITION, 1, 1, 1)

#define EXPECT_COMPILE_TIME(CONDITION)         K3_TESTING_GENERIC_CHECK_(CONDITION, 1, 0, 0)
#define EXPECT_RUN_TIME(CONDITION)             K3_TESTING_GENERIC_CHECK_(CONDITION, 0, 1, 0)
#define EXPECT_COMPILE_AND_RUN_TIME(CONDITION) K3_TESTING_GENERIC_CHECK_(CONDITION, 1, 1, 0)



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
    } static_assert(true, "require semicolon")

// EXPECT_THAT ignores all the internal non-fatal errors,
// but it cannot ignore the fatal errors.
#define EXPECT_THAT(FRAGMENT)                        \
    {                                                \
        ::k3::testing::context::trace_context _ctx_; \
        (FRAGMENT)();                                \
    } static_assert(true, "require semicolon")



#define ASSERT(CONDITION) \
    ASSERT_COMPILE_AND_RUN_TIME(CONDITION)

#define EXPECT(CONDITION) \
    EXPECT_COMPILE_AND_RUN_TIME(CONDITION)

#endif // K3_TOK3N_TESTS_FRAMEWORK_ASSERT_HPP
