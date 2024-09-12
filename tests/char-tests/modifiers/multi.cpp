#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("multi operator");

TEST("multi operator", "creation")
{
	ASSERT_MODIFIER_VALUES_EQ(ignore % join, (multi_modifier<ignore_modifier, join_modifier>{}));
	ASSERT_MODIFIER_VALUES_EQ(join % ignore, (multi_modifier<join_modifier, ignore_modifier>{}));
	ASSERT_MODIFIER_VALUES_EQ(complete % join, (multi_modifier<complete_modifier, join_modifier>{}));
	ASSERT_MODIFIER_VALUES_EQ(join % complete, (multi_modifier<join_modifier, complete_modifier>{}));
	ASSERT_MODIFIER_VALUES_EQ(ignore % complete, (multi_modifier<ignore_modifier, complete_modifier>{}));
	ASSERT_MODIFIER_VALUES_EQ(complete % ignore, (multi_modifier<complete_modifier, ignore_modifier>{}));
}

TEST("multi operator", "not commutative")
{
	ASSERT_MODIFIER_VALUES_NE((ignore % join), (join % ignore));
	ASSERT_MODIFIER_VALUES_NE((complete % join), (join % complete));
	ASSERT_MODIFIER_VALUES_NE((ignore % complete), (complete % ignore));
}

TEST("multi operator", "associative")
{
	ASSERT_MODIFIER_VALUES_EQ(((ignore % join) % complete) % into<Sink>, (ignore % (join % complete)) % into<Sink>);
	ASSERT_MODIFIER_VALUES_EQ(((ignore % join) % complete) % into<Sink>, (ignore % join) % (complete % into<Sink>));
	ASSERT_MODIFIER_VALUES_EQ(((ignore % join) % complete) % into<Sink>, ignore % ((join % complete) % into<Sink>));
	ASSERT_MODIFIER_VALUES_EQ(((ignore % join) % complete) % into<Sink>, ignore % (join % (complete % into<Sink>)));
}

TEST("multi operator", "applying the modifier")
{
	ASSERT_PARSER_VALUES_EQ(oom1 % (join % ignore % complete), Complete<Ignore<Join<Oom1>>>{});
	ASSERT_PARSER_VALUES_EQ(oom1 % (join % complete % ignore), Ignore<Complete<Join<Oom1>>>{});
}
