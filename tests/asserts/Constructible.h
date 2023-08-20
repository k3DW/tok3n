#pragma once
#include "framework/Assert.h"
#include <k3/tok3n/types/StaticString.h>

template <template <class...> class ParserFamily, class... Args>
concept constructible_from = requires { typename ParserFamily<Args...>; };

template <template <k3::tok3n::StaticString> class ParserFamily, k3::tok3n::StaticString str>
concept basic_constructible_from = requires { typename ParserFamily<str>; };

#define ASSERT_PARSER_CONSTRUCTIBLE(FAMILY, ...)                           \
	ASSERT((constructible_from<FAMILY __VA_OPT__(,) __VA_ARGS__>),         \
		"A " #FAMILY " parser should be constructible from " #__VA_ARGS__)

#define ASSERT_PARSER_NOT_CONSTRUCTIBLE(FAMILY, ...)                           \
	ASSERT((not constructible_from<FAMILY __VA_OPT__(,) __VA_ARGS__>),         \
		"A " #FAMILY " parser should not be constructible from " #__VA_ARGS__)

#define ASSERT_BASIC_PARSER_CONSTRUCTIBLE(FAMILY, STRING)             \
	ASSERT((basic_constructible_from<FAMILY, STRING>),                \
		"A " #FAMILY " parser should be constructible from " #STRING)

#define ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(FAMILY, STRING)             \
	ASSERT((not basic_constructible_from<FAMILY, STRING>),                \
		"A " #FAMILY " parser should not be constructible from " #STRING)
