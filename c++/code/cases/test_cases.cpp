#include "../src/testFrame/test_frame.h"

using namespace Frame;
namespace Test {
TEST(math, add)
{
    EXPECT_TRUE(2 + 3 == 5);
}

TEST(math, add_fail)
{
    EXPECT_FALSE(2 + 3 == 4);
}

TEST(math, eq)
{
    EXPECT_EQ(2, 2);
    EXPECT_EQ("abc", "abc");
}

TEST(math, eq_fail)
{
    EXPECT_NE(2, 3);
    EXPECT_NE("abc", "abc ");
}
}  // namespace Test
