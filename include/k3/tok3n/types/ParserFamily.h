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

constexpr ParserFamily AnyOfType          = ParserFamily::AnyOf;
constexpr ParserFamily NoneOfType         = ParserFamily::NoneOf;
constexpr ParserFamily AllOfType          = ParserFamily::AllOf;
constexpr ParserFamily ChoiceType         = ParserFamily::Choice;
constexpr ParserFamily SequenceType       = ParserFamily::Sequence;
constexpr ParserFamily MaybeType          = ParserFamily::Maybe;
constexpr ParserFamily ExactlyType        = ParserFamily::Exactly;
constexpr ParserFamily OneOrMoreType      = ParserFamily::OneOrMore;
constexpr ParserFamily ZeroOrMoreType     = ParserFamily::ZeroOrMore;
constexpr ParserFamily DelimitType        = ParserFamily::Delimit;
constexpr ParserFamily IgnoreType         = ParserFamily::Ignore;
constexpr ParserFamily CompleteType       = ParserFamily::Complete;
constexpr ParserFamily JoinType           = ParserFamily::Join;
constexpr ParserFamily TransformType      = ParserFamily::Transform;
constexpr ParserFamily ApplyTransformType = ParserFamily::ApplyTransform;
constexpr ParserFamily IntoType           = ParserFamily::Into;
constexpr ParserFamily ApplyIntoType      = ParserFamily::ApplyInto;
constexpr ParserFamily ConstantType       = ParserFamily::Constant;
constexpr ParserFamily DefaultedType      = ParserFamily::Defaulted;
constexpr ParserFamily CustomType         = ParserFamily::Custom;

} // namespace k3::tok3n
