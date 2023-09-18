#include "../src/testFrame/test_frame.h"

using namespace Frame;
namespace Test {
TEST(math, add)
{
    EXPECT_TRUE(2 + 3 == 5);
}

TEST(math, add_fail)
{
    EXPECT_TRUE(2 + 3 == 4);
}
}  // namespace Test
