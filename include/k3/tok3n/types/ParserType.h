#pragma once

namespace k3::tok3n {

enum class ParserType
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

constexpr ParserType AnyOfType        = ParserType::AnyOf;
constexpr ParserType NoneOfType        = ParserType::NoneOf;
constexpr ParserType AllOfType        = ParserType::AllOf;
constexpr ParserType ChoiceType         = ParserType::Choice;
constexpr ParserType SequenceType       = ParserType::Sequence;
constexpr ParserType MaybeType          = ParserType::Maybe;
constexpr ParserType ExactlyType        = ParserType::Exactly;
constexpr ParserType OneOrMoreType      = ParserType::OneOrMore;
constexpr ParserType ZeroOrMoreType     = ParserType::ZeroOrMore;
constexpr ParserType DelimitType        = ParserType::Delimit;
constexpr ParserType IgnoreType         = ParserType::Ignore;
constexpr ParserType CompleteType       = ParserType::Complete;
constexpr ParserType JoinType           = ParserType::Join;
constexpr ParserType TransformType      = ParserType::Transform;
constexpr ParserType ApplyTransformType = ParserType::ApplyTransform;
constexpr ParserType IntoType           = ParserType::Into;
constexpr ParserType ApplyIntoType      = ParserType::ApplyInto;
constexpr ParserType ConstantType       = ParserType::Constant;
constexpr ParserType DefaultedType      = ParserType::Defaulted;
constexpr ParserType CustomType         = ParserType::Custom;

} // namespace k3::tok3n
