//
// Created by JoachimWagner on 16.11.2026.
//

#include "WagnerStackTest.h"

TEST_F(WagnerStackTest, IsEmpty__EmptyStack__ReturnsTrue) {
    EXPECT_THAT(objectUnderTest.IsEmpty(), Eq(true));
}

TEST_F(WagnerStackTest, IsEmpty__NotEmptyStack__ReturnsFalse) {
    objectUnderTest.push(1);
    EXPECT_THAT(objectUnderTest.IsEmpty(), Eq(false));
}
