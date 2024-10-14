// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include "framework/Assert.h"
#include <k3/tok3n/detail/static_array.h>

template <template <class...> class Family, class... Args>
concept constructible_from = requires { typename Family<Args...>; };

template <template <k3::tok3n::detail::static_array> class Family, k3::tok3n::detail::static_array arr>
concept basic_constructible_from = requires { typename Family<arr>; };

#define ASSERT_PARSER_CONSTRUCTIBLE(FAMILY, ...)                                          \
	ASSERT((constructible_from<FAMILY __VA_OPT__(,) __VA_ARGS__>),                        \
		"A `" STR(FAMILY) "` parser should be constructible from `" STR(__VA_ARGS__) "`")

#define ASSERT_PARSER_NOT_CONSTRUCTIBLE(FAMILY, ...)                                          \
	ASSERT((not constructible_from<FAMILY __VA_OPT__(,) __VA_ARGS__>),                        \
		"A `" STR(FAMILY) "` parser should not be constructible from `" STR(__VA_ARGS__) "`")

#define ASSERT_BASIC_PARSER_CONSTRUCTIBLE(FAMILY, STRING)                            \
	ASSERT((basic_constructible_from<FAMILY, STRING>),                               \
		"A `" STR(FAMILY) "` parser should be constructible from `" STR(STRING) "`")

#define ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(FAMILY, STRING)                            \
	ASSERT((not basic_constructible_from<FAMILY, STRING>),                               \
		"A `" STR(FAMILY) "` parser should not be constructible from `" STR(STRING) "`")
