#pragma once

namespace k3::tok3n {

enum class ParserFamily
{
	None,

	AnyOf,
	NoneOf,
	AllOf,
	Anything,
	Epsilon,
	Choice,
	Sequence,
	Maybe,
	Exactly,
	OneOrMore,
	ZeroOrMore,
	Delimit,
	Ignore,
	Complete,
	Join,
	Map,
	Named,
	Custom,

	END
};

inline constexpr ParserFamily AnyOfFamily          = ParserFamily::AnyOf;
inline constexpr ParserFamily NoneOfFamily         = ParserFamily::NoneOf;
inline constexpr ParserFamily AllOfFamily          = ParserFamily::AllOf;
inline constexpr ParserFamily AnythingFamily       = ParserFamily::Anything;
inline constexpr ParserFamily EpsilonFamily        = ParserFamily::Epsilon;
inline constexpr ParserFamily ChoiceFamily         = ParserFamily::Choice;
inline constexpr ParserFamily SequenceFamily       = ParserFamily::Sequence;
inline constexpr ParserFamily MaybeFamily          = ParserFamily::Maybe;
inline constexpr ParserFamily ExactlyFamily        = ParserFamily::Exactly;
inline constexpr ParserFamily OneOrMoreFamily      = ParserFamily::OneOrMore;
inline constexpr ParserFamily ZeroOrMoreFamily     = ParserFamily::ZeroOrMore;
inline constexpr ParserFamily DelimitFamily        = ParserFamily::Delimit;
inline constexpr ParserFamily IgnoreFamily         = ParserFamily::Ignore;
inline constexpr ParserFamily CompleteFamily       = ParserFamily::Complete;
inline constexpr ParserFamily NamedFamily          = ParserFamily::Named;
inline constexpr ParserFamily JoinFamily           = ParserFamily::Join;
inline constexpr ParserFamily MapFamily            = ParserFamily::Map;
inline constexpr ParserFamily CustomFamily         = ParserFamily::Custom;

} // namespace k3::tok3n
