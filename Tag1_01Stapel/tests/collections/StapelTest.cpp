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

    fillUpToLimit();


}
TEST_F(StapelTest, push__FillUpToLimit__StapelExceptionIsThrown) {

    fillUpToLimit();

    EXPECT_THAT([&]() { this->objectUnderTest.push(1); },
                ThrowsMessage<StapelException>(HasSubstr("Overflow")));
}

TEST_F(StapelTest, isFull__NotFullStack__ReturnFalse) {
    // Arrange + Action
    auto result = objectUnderTest.isFull();

    // Assertion
    EXPECT_THAT(result, IsFalse());
}

TEST_F(StapelTest, isFull__NineElements__ReturnFalse) {
    // Arrange
    for (int i = 0; i < 9; i++) {
        objectUnderTest.push(1);
    }

    // Action
    auto result = objectUnderTest.isFull();

    // Assertion
    EXPECT_THAT(result, IsFalse());
}

TEST_F(StapelTest, isFull__TenElements__ReturnTrue) {
    // Arrange
    fillUpToLimit();

    // Action
    auto result = objectUnderTest.isFull();

    // Assertion
    EXPECT_THAT(result, IsTrue());
}

TEST_F(StapelTest, isFull__FullStackAfterPop__ReturnFalse) {
    // Arrange
    for (int i = 0; i < 10; i++) {
        objectUnderTest.push(1);
    }
    objectUnderTest.pop();

    // Action
    auto result = objectUnderTest.isFull();

    // Assertion
    EXPECT_THAT(result, IsFalse());
}
