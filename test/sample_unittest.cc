#include "sample.h"
#include "gtest/gtest.h"

namespace {

//First Argument is the test label
//Second Argument is the type of case you are testing out

    
//Test factorial of positive numbers    
TEST(FactorialTest, Positive ) {
    EXPECT_EQ(1, Factorial(1));
    EXPECT_EQ(2, Factorial(2));
    EXPECT_EQ(6, Factorial(3));
} 

//Test factorial of 0
TEST(FactorialTest, Zero) {
    EXPECT_EQ(1, Factorial(0));
}

}
