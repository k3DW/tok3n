#pragma once

namespace k3::tok3n {

enum class ParserFamily
{
	None,

	AnyOf,
	NoneOf,
	AllOf,
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
	Transform,
	ApplyTransform,
	Into,
	ApplyInto,
	Constant,
	Defaulted,
	Custom,

	END
};

constexpr ParserFamily AnyOfFamily          = ParserFamily::AnyOf;
constexpr ParserFamily NoneOfFamily         = ParserFamily::NoneOf;
constexpr ParserFamily AllOfFamily          = ParserFamily::AllOf;
constexpr ParserFamily ChoiceFamily         = ParserFamily::Choice;
constexpr ParserFamily SequenceFamily       = ParserFamily::Sequence;
constexpr ParserFamily MaybeFamily          = ParserFamily::Maybe;
constexpr ParserFamily ExactlyFamily        = ParserFamily::Exactly;
constexpr ParserFamily OneOrMoreFamily      = ParserFamily::OneOrMore;
constexpr ParserFamily ZeroOrMoreFamily     = ParserFamily::ZeroOrMore;
constexpr ParserFamily DelimitFamily        = ParserFamily::Delimit;
constexpr ParserFamily IgnoreFamily         = ParserFamily::Ignore;
constexpr ParserFamily CompleteFamily       = ParserFamily::Complete;
constexpr ParserFamily JoinFamily           = ParserFamily::Join;
constexpr ParserFamily TransformFamily      = ParserFamily::Transform;
constexpr ParserFamily ApplyTransformFamily = ParserFamily::ApplyTransform;
constexpr ParserFamily IntoFamily           = ParserFamily::Into;
constexpr ParserFamily ApplyIntoFamily      = ParserFamily::ApplyInto;
constexpr ParserFamily ConstantFamily       = ParserFamily::Constant;
constexpr ParserFamily DefaultedFamily      = ParserFamily::Defaulted;
constexpr ParserFamily CustomFamily         = ParserFamily::Custom;

} // namespace k3::tok3n
