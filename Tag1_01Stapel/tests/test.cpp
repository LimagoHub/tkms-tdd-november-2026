#include "gtest/gtest.h"

#include "greeting.hpp"

TEST(GreetingTest, ReturnsHallo) {
    ASSERT_EQ("Hallo", greeting());
    EXPECT_EQ("Hallo", greeting());
}
