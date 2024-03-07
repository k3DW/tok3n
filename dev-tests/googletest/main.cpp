#include <gtest/gtest.h>
#include <k3/tok3n.h>
#include <iostream>

auto p = k3::tok3n::any<"123"> >> k3::tok3n::any<"abc">;

TEST(ABC, ABCDEFG)
{
    EXPECT_EQ(p.family, k3::tok3n::ParserFamily::Sequence);
    EXPECT_TRUE(p.parse("1a").has_value());
    EXPECT_EQ(*p.parse("1a"), std::tuple("1", "a"));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
