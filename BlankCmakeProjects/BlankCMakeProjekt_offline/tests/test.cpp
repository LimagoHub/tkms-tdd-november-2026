#include "gtest/gtest.h"

#include "greeting.hpp"

TEST(GreetingTest, ReturnsHallo) {
    EXPECT_EQ("Hallo", greeting());
}
