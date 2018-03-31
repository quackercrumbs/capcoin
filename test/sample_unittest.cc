#include "sample.h"
#include "gtest/gtest.h"

namespace {

TEST(testerTest, AddOne) {
    EXPECT_EQ(1, tester(0));
    EXPECT_EQ(2, tester(1));
    EXPECT_GT(4, tester(2));
} 

}
