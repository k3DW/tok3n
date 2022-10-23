#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

#include "tok3n/parsers/basic/OneChar.h"
#include "tok3n/parsers/basic/NotChar.h"
#include "tok3n/parsers/basic/Literal.h"

#include "tok3n/parsers/compound/Choice.h"
#include "tok3n/parsers/compound/Sequence.h"

#include "tok3n/parsers/repeat/Maybe.h"
#include "tok3n/parsers/repeat/Exactly.h"
#include "tok3n/parsers/repeat/OneOrMore.h"
#include "tok3n/parsers/repeat/ZeroOrMore.h"
#include "tok3n/parsers/repeat/Ignore.h"

#include "tok3n/parsers/adaptor/Transform.h"
#include "tok3n/parsers/adaptor/Join.h"
#include "tok3n/parsers/adaptor/Delimit.h"
#include "tok3n/parsers/adaptor/Into.h"
#include "tok3n/parsers/adaptor/Constant.h"
#include "tok3n/parsers/adaptor/Defaulted.h"
#include "tok3n/parsers/adaptor/Complete.h"
#include "tok3n/parsers/adaptor/Custom.h"

#include "tok3n/operators/Not.h"
#include "tok3n/operators/Choice.h"
#include "tok3n/operators/Sequence.h"
#include "tok3n/operators/Maybe.h"
#include "tok3n/operators/OneOrMore.h"
#include "tok3n/operators/ZeroOrMore.h"
#include "tok3n/operators/Modifier.h"
