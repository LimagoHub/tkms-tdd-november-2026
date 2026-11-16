//
// Created by JoachimWagner on 16.11.2026.
//

#include "MyServiceUsingDependencyTest.h"


/*
  *  1. Foo wird mit kardinalität 1 aufgerufen
  *  2. Parameter wurde in Grossbuchstaben gewandelt
  *  3. korrekter call mit richtigem parameter
  *
  *
 void f(std::string value) {
     transform(value.begin(), value.end(), value.begin(), ::toupper);
     dependency.foo(value);

 }
 */
TEST_F(MyServiceUsingDependencyTest, MockdemoFooFunc) {

    // Arrange + Assertion
    // Recordmode
    EXPECT_CALL(dependencyMock, foo("HALLO")).Times(1);
    EXPECT_CALL(dependencyMock, foo("HELLO")).Times(1);


    // Replay

    objectUnderTest.f("hallo");
    objectUnderTest.f("hello");

}
/*
size_t g(std::string value) {
    value += " Welt";

    return dependency.foobar(value) + 5;
}
*/
TEST_F(MyServiceUsingDependencyTest, MockdemoFooBarFunc) {
    EXPECT_CALL(dependencyMock, foobar("Hallo Welt"))
        .Times(AtLeast(1))
        .WillOnce(Return(10))
        .WillOnce(Return(15))
        .WillOnce(Throw(std::exception{}));

    EXPECT_THAT(objectUnderTest.g("Hallo"), Eq(15));
    EXPECT_THAT(objectUnderTest.g("Hallo"), Eq(20));
    //EXPECT_THAT(objectUnderTest.g("Hallo"), Eq(20));
}

/*
 *
*    long h() {
const auto barValue = dependency.bar();
return barValue * barValue;

}
*/
TEST_F(MyServiceUsingDependencyTest, MockdemoBarFunc) {
    EXPECT_CALL(dependencyMock, bar()).Times(1).WillOnce(Return(3));
    // Action
    const auto result = objectUnderTest.h();
    // Assertion
    EXPECT_THAT(result, Eq(9));
}