// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_CONFIG_HPP
#define K3_TOK3N_TESTS_COMMON_CONFIG_HPP

#if defined(_MSC_VER)
#define DEP_TEMPLATE
#else
#define DEP_TEMPLATE template
#endif

#if defined(__GNUC__) and (__GNUC__ <= 12)
#define TEMPLATE_IF_GCC12 template
#else
#define TEMPLATE_IF_GCC12
#endif

#endif // K3_TOK3N_TESTS_COMMON_CONFIG_HPP
