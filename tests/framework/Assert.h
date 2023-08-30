#pragma once

// #define DISABLE_STATIC_ASSERT

#ifdef DISABLE_STATIC_ASSERT
#define STATIC_ASSERT(...)
#else
#define STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#endif

#define REQUIRE_SEMICOLON static_assert(true, "require semicolon")

#define ASSERT(CONDITION, MESSAGE)                        \
	{                                                     \
		STATIC_ASSERT(CONDITION, MESSAGE);                \
		if (!TestResultContext::check(CONDITION))         \
			return TestResultContext::add_error(MESSAGE); \
	} REQUIRE_SEMICOLON



#define IDENTITY(...) __VA_ARGS__

#define STR(...) #__VA_ARGS__
