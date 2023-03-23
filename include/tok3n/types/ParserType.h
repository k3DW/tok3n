#pragma once
#include <tok3n/utilities/namespace.h>

TOK3N_BEGIN_NAMESPACE()

enum class ParserType
{
	None,
	OneChar,
	NotChar,
	Literal,
	Choice,
	Sequence,
	OneOrMore,
	ZeroOrMore,
	Maybe,
	Exactly,
	Ignore,
	Transform,
	ApplyTransform,
	Join,
	Delimit,
	Into,
	ApplyInto,
	Constant,
	Defaulted,
	Complete,
	Custom,
	END
};

TOK3N_END_NAMESPACE()
