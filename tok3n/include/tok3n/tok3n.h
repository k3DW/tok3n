#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

#include "tok3n/parsers/basic/OneChar.h"
#include "tok3n/parsers/basic/NotChar.h"
#include "tok3n/parsers/basic/Literal.h"

#include "tok3n/parsers/compound/Choice.h"
#include "tok3n/parsers/compound/Sequence.h"

#include "tok3n/parsers/repeat/OneOrMore.h"
#include "tok3n/parsers/repeat/ZeroOrMore.h"
#include "tok3n/parsers/repeat/ZeroOrOne.h"

#include "tok3n/parsers/adaptor/Transform.h"
#include "tok3n/parsers/adaptor/Flatten.h"
#include "tok3n/parsers/adaptor/Ignore.h"
#include "tok3n/parsers/adaptor/Delimit.h"

#include "tok3n/operators/Not.h"
#include "tok3n/operators/Choice.h"
#include "tok3n/operators/Sequence.h"
#include "tok3n/operators/OneOrMore.h"
#include "tok3n/operators/ZeroOrMore.h"
#include "tok3n/operators/ZeroOrOne.h"
#include "tok3n/operators/Adaptor.h"
