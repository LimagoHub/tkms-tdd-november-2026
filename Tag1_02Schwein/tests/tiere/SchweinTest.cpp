//
// Created by JoachimWagner on 19.08.2024.
//

#include "SchweinTest.h"

const int MyInitialWeight = 10;


TEST_F(SchweinTest, ctor__default__correctInitialisation){
    std::string expectedValue = "Nobody";



    EXPECT_THAT(objectUnderTest.get_gewicht(), Eq(MyInitialWeight));
    EXPECT_THAT(objectUnderTest.get_name(), Eq(expectedValue));

}

TEST_F(SchweinTest, ctor__overloaded_with_invalid_name__throwsInvalidArgument){

    const std::string invalidName = "Elsa";


    EXPECT_THAT([&]() { Schwein objectUnderTestLocal{invalidName}; },
                ThrowsMessage<std::invalid_argument>(Eq("Name verstoesst gegen die Schweinewuerde!")));

}

TEST_F(SchweinTest, ctor__overloaded_with_valid_name__correctInitialisation){
        const std::string validName = "Piggy";
        Schwein objectUnderTestLocal{validName};
        EXPECT_THAT( objectUnderTestLocal.get_gewicht(), MyInitialWeight);
        EXPECT_THAT( objectUnderTestLocal.get_name(), validName);

}

TEST_F(SchweinTest, setName__invalidName__throwsInvalidArgument){

        const std::string invalidName = "Elsa";
        EXPECT_THAT([&]() { this->objectUnderTest.set_name(invalidName); },
              ThrowsMessage<std::invalid_argument>(Eq("Name verstoesst gegen die Schweinewuerde!")));


}

TEST_F(SchweinTest, setName__validName__nameCorrectlySetAndNoExceptionIsThrown){

    const std::string validName = "Piggy";

    EXPECT_THAT([&](){ objectUnderTest.set_name(validName); }, Not(Throws<std::exception>()));
    EXPECT_THAT(objectUnderTest.get_name(),Eq("Piggy") );
}

TEST_F(SchweinTest, fuettern__happyDay__weightIncreasedByOne){

    const auto expectedResult = MyInitialWeight + 1;
    objectUnderTest.fuettern();
    EXPECT_THAT( objectUnderTest.get_gewicht(), Eq(expectedResult));
}

// =====================================================================
// Alternative Benennung: "Should"-Stil (gleiche Tests, andere Namen)
// =====================================================================

TEST_F(SchweinTest, ShouldHaveDefaultNameAndInitialWeight_WhenDefaultConstructed){
    std::string expectedValue = "Nobody";

    EXPECT_THAT(objectUnderTest.get_gewicht(), Eq(MyInitialWeight));
    EXPECT_THAT(objectUnderTest.get_name(), Eq(expectedValue));
}

TEST_F(SchweinTest, ShouldThrowInvalidArgument_WhenConstructedWithInvalidName){
    const std::string invalidName = "Elsa";

    EXPECT_THAT([&]() { Schwein objectUnderTestLocal{invalidName}; },
                ThrowsMessage<std::invalid_argument>(Eq("Name verstoesst gegen die Schweinewuerde!")));
}

TEST_F(SchweinTest, ShouldHaveGivenNameAndInitialWeight_WhenConstructedWithValidName){
    const std::string validName = "Piggy";
    Schwein objectUnderTestLocal{validName};

    EXPECT_THAT(objectUnderTestLocal.get_gewicht(), MyInitialWeight);
    EXPECT_THAT(objectUnderTestLocal.get_name(), validName);
}

TEST_F(SchweinTest, ShouldThrowInvalidArgument_WhenNameIsSetToInvalidName){
    const std::string invalidName = "Elsa";

    EXPECT_THAT([&]() { this->objectUnderTest.set_name(invalidName); },
                ThrowsMessage<std::invalid_argument>(Eq("Name verstoesst gegen die Schweinewuerde!")));
}

TEST_F(SchweinTest, ShouldStoreNameWithoutThrowing_WhenNameIsSetToValidName){
    const std::string validName = "Piggy";

    EXPECT_THAT([&](){ objectUnderTest.set_name(validName); }, Not(Throws<std::exception>()));
    EXPECT_THAT(objectUnderTest.get_name(), Eq("Piggy"));
}

TEST_F(SchweinTest, ShouldIncreaseWeightByOne_WhenFed){
    const auto expectedResult = MyInitialWeight + 1;

    objectUnderTest.fuettern();

    EXPECT_THAT(objectUnderTest.get_gewicht(), Eq(expectedResult));
}
