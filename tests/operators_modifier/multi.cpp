#include "pch.h"

TEST("multi operator", "creation")
{
	assert
		, ignore % join == modifiers::multi<modifiers::ignore, modifiers::join>{}
		, join % ignore == modifiers::multi<modifiers::join, modifiers::ignore>{}
		, complete % join == modifiers::multi<modifiers::complete, modifiers::join>{}
		, join % complete == modifiers::multi<modifiers::join, modifiers::complete>{}
		, ignore % complete == modifiers::multi<modifiers::ignore, modifiers::complete>{}
		, complete % ignore == modifiers::multi<modifiers::complete, modifiers::ignore>{}
		;
}

TEST("multi operator", "not commutative")
{
	assert
		, (ignore % join) != (join % ignore)
		, (complete % join) != (join % complete)
		, (ignore % complete) != (complete % ignore)
		;
}

TEST("multi operator", "associative")
{
	assert
		, ((ignore % join) % complete) % into<Sink> == (ignore % (join % complete)) % into<Sink>
		, ((ignore % join) % complete) % into<Sink> == (ignore % join) % (complete % into<Sink>)
		, ((ignore % join) % complete) % into<Sink> == ignore % ((join % complete) % into<Sink>)
		, ((ignore % join) % complete) % into<Sink> == ignore % (join % (complete % into<Sink>))
		;
}

TEST("multi operator", "applying the modifier")
{
	assert
		, oom1 % (join % ignore % complete) == Complete<Ignore<Join<Oom1>>>{}
		, oom1 % (join % complete % ignore) == Ignore<Complete<Join<Oom1>>>{}
		;
}
