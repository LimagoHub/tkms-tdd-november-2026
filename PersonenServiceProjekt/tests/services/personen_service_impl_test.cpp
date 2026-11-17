//
// Created by JoachimWagner on 15.12.2025.
//
#include <stdexcept>
#include "personen_service_impl_test.h"

TEST_F(personen_service_impl_test, speichern__vornameZuKurz__throwsPersonenServiceException) {
    // Arrange
    person invalidPerson{"", "Doe"};

    // Act + Assert
    EXPECT_THAT([&]() { objectUnderTest.speichern(invalidPerson); },ThrowsMessage<personen_service_exception>(StrEq("Vorname zu kurz!")));

}

TEST_F(personen_service_impl_test, speichern__nachNameZuKurz__throwsPersonenServiceException) {
    // Arrange
    person invalidPerson{"John", ""};

    // Act + Assert
    EXPECT_THAT([&]() { objectUnderTest.speichern(invalidPerson); },ThrowsMessage<personen_service_exception>(StrEq("Nachname zu kurz!")));
}

TEST_F(personen_service_impl_test,speichern__Antipath__throwsPersonenServiceException) {
    // Arrange
    person invalidPerson{"Attila", "der Hunnenkoenig"};


    // Act + Assert
    EXPECT_THAT([&]() { objectUnderTest.speichern(invalidPerson); },ThrowsMessage<personen_service_exception>(StrEq("Unerwuensche Person")));
}

TEST_F(personen_service_impl_test,speichern__UnexpectedExceptionInUnderlyingService__throws_personen_service_exception) {
    // Arrange
    person validPerson{"John", "Doe"};

    EXPECT_CALL(repoMock, save_or_update(_)).WillOnce(Throw(std::runtime_error{"upps"}));

    EXPECT_THAT([&]() { objectUnderTest.speichern(validPerson); },ThrowsMessage<personen_service_exception>(StrEq("Ein Fehler ist aufgetreten!")));
}