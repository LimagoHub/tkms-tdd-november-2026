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