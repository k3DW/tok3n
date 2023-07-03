#pragma once
#include "Test.h"

#define TOK3N_ASSERT_PARSER_CONCEPT(P)                   \
	TOK3N_ASSERT(Parser<P>,                              \
		"(" #P ") does not satisfy the Parser concept.")

#define TOK3N_ASSERT_PARSE_VALID(P, INPUT)                                           \
	TOK3N_ASSERT((P::parse(INPUT)).has_value(),                                      \
		"(" #P "::parse(" #INPUT ")) does not give a valid result, but it should." )

#define TOK3N_ASSERT_PARSE_INVALID(P, INPUT)                                     \
	TOK3N_ASSERT(not (P::parse(INPUT)).has_value(),                              \
		"(" #P "::parse(" #INPUT ")) gives a valid result, but it should not." )

#define TOK3N_ASSERT_PARSE_RESULT(P, INPUT, OUTPUT)                  \
	TOK3N_ASSERT(*(P::parse(INPUT)) == (OUTPUT),                     \
		"*(" #P "::parse(" #INPUT ")) does not equal (" #OUTPUT ")")

#define TOK3N_ASSERT_PARSE_REMAINING(P, INPUT, REMAINING)                          \
	TOK3N_ASSERT((P::parse(INPUT)).remaining() == (REMAINING),                     \
		"(" #P "::parse(" #INPUT ")).remaining() does not equal (" #REMAINING ")")

#define TOK3N_ASSERT_LOOKAHEAD_VALID(P, INPUT)                                           \
	TOK3N_ASSERT((P::lookahead(INPUT)).has_value(),                                      \
		"(" #P "::lookahead(" #INPUT ")) does not give a valid result, but it should." )

#define TOK3N_ASSERT_LOOKAHEAD_INVALID(P, INPUT)                                     \
	TOK3N_ASSERT(not (P::lookahead(INPUT)).has_value(),                              \
		"(" #P "::lookahead(" #INPUT ")) gives a valid result, but it should not." )

#define TOK3N_ASSERT_LOOKAHEAD_REMAINING(P, INPUT, REMAINING)                          \
	TOK3N_ASSERT((P::lookahead(INPUT)).remaining() == (REMAINING),                     \
		"(" #P "::lookahead(" #INPUT ")).remaining() does not equal (" #REMAINING ")")

#define TOK3N_ASSERT_SUCCESS(P, INPUT, OUTPUT, REMAINING)      \
	do {                                                       \
		TOK3N_ASSERT_PARSER_CONCEPT(P);                        \
		if (TOK3N_ASSERT_PARSE_VALID(P, INPUT))                \
		{                                                      \
			TOK3N_ASSERT_PARSE_RESULT(P, INPUT, OUTPUT);       \
		}                                                      \
		TOK3N_ASSERT_PARSE_REMAINING(P, INPUT, REMAINING);     \
		TOK3N_ASSERT_LOOKAHEAD_VALID(P, INPUT);                \
		TOK3N_ASSERT_LOOKAHEAD_REMAINING(P, INPUT, REMAINING); \
	} while (false)

#define TOK3N_ASSERT_SUCCESS_VOID(P, INPUT, REMAINING)         \
	do {                                                       \
		TOK3N_ASSERT_PARSER_CONCEPT(P);                        \
		TOK3N_ASSERT_PARSE_VALID(P, INPUT);                    \
		TOK3N_ASSERT_PARSE_REMAINING(P, INPUT, REMAINING);     \
		TOK3N_ASSERT_LOOKAHEAD_VALID(P, INPUT);                \
		TOK3N_ASSERT_LOOKAHEAD_REMAINING(P, INPUT, REMAINING); \
	} while (false)

#define TOK3N_ASSERT_FAILURE(P, INPUT)                     \
	do {                                                   \
		TOK3N_ASSERT_PARSER_CONCEPT(P);                    \
		TOK3N_ASSERT_PARSE_INVALID(P, INPUT);              \
		TOK3N_ASSERT_PARSE_REMAINING(P, INPUT, INPUT);     \
		TOK3N_ASSERT_LOOKAHEAD_INVALID(P, INPUT);          \
		TOK3N_ASSERT_LOOKAHEAD_REMAINING(P, INPUT, INPUT); \
	} while (false)

#define TOK3N_ASSERT_LOOKAHEAD_ONLY(P, INPUT, REMAINING)       \
	do {                                                       \
		TOK3N_ASSERT_PARSER_CONCEPT(P);                        \
		TOK3N_ASSERT_PARSE_INVALID(P, INPUT);                  \
		TOK3N_ASSERT_PARSE_REMAINING(P, INPUT, INPUT);         \
		TOK3N_ASSERT_LOOKAHEAD_VALID(P, INPUT);                \
		TOK3N_ASSERT_LOOKAHEAD_REMAINING(P, INPUT, REMAINING); \
	} while (false)
