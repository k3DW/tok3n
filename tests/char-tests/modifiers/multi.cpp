#include "samples.h"

FIXTURE("multi operator");

TEST("multi operator", "creation")
{
	ASSERT_MODIFIER_VALUES_EQ(ignore % join, (modifiers::multi<modifiers::ignore, modifiers::join>{}));
	ASSERT_MODIFIER_VALUES_EQ(join % ignore, (modifiers::multi<modifiers::join, modifiers::ignore>{}));
	ASSERT_MODIFIER_VALUES_EQ(complete % join, (modifiers::multi<modifiers::complete, modifiers::join>{}));
	ASSERT_MODIFIER_VALUES_EQ(join % complete, (modifiers::multi<modifiers::join, modifiers::complete>{}));
	ASSERT_MODIFIER_VALUES_EQ(ignore % complete, (modifiers::multi<modifiers::ignore, modifiers::complete>{}));
	ASSERT_MODIFIER_VALUES_EQ(complete % ignore, (modifiers::multi<modifiers::complete, modifiers::ignore>{}));
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
