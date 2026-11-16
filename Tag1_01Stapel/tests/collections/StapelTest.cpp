//
// Created by JoachimWagner on 16.11.2026.
//

#include "StapelTest.h"

TEST_F(StapelTest,isEmpty__EmptyStack__ReturnTrue) {
    // Arrange + Act + Assertion
    EXPECT_THAT(objectUnderTest.isEmpty(), IsTrue());
}

TEST_F(StapelTest,isEmpty__NotEmptyStack__ReturnFalse) {
    // Arrange

   objectUnderTest.push(1);

    // Action
    auto result = objectUnderTest.isEmpty();

    //EXPECT_TRUE(result);
    EXPECT_THAT(result, IsFalse());
}

TEST_F(StapelTest, push__FillUpToLimit__NoExceptionIsThrown) {

        for (int i = 0; i < 10; i++) {
            EXPECT_NO_THROW(objectUnderTest.push(1));
        }


}
TEST_F(StapelTest, push__FillUpToLimit__StapelExceptionIsThrown) {

    for (int i = 0; i < 10; i++) {
        EXPECT_NO_THROW(objectUnderTest.push(1));
    }

    EXPECT_THAT([&]() { this->objectUnderTest.push(1); },
                ThrowsMessage<StapelException>(HasSubstr("Overflow")));
}