//
// Created by JoachimWagner on 15.12.2025.
//
#include <stdexcept>
#include "personen_service_impl_test.h"

TEST_F(personen_service_impl_test, speichern__vornameZuKurz__throwsPersonenServiceException) {
    // Arrange
    person invalidPerson{"", "Doe"};

    EXPECT_CALL(repoMock,save_or_update(_) ).Times(0);
    // Act + Assert
    EXPECT_THAT([&]() { objectUnderTest.speichern(invalidPerson); },ThrowsMessage<personen_service_exception>(StrEq("Vorname zu kurz!")));

}

TEST_F(personen_service_impl_test, speichern__nachNameZuKurz__throwsPersonenServiceException) {
    // Arrange
    person invalidPerson{"John", ""};
    EXPECT_CALL(repoMock,save_or_update(_) ).Times(0);
    // Act + Assert
    EXPECT_THAT([&]() { objectUnderTest.speichern(invalidPerson); },ThrowsMessage<personen_service_exception>(StrEq("Nachname zu kurz!")));
}

TEST_F(personen_service_impl_test,speichern__Antipath__throwsPersonenServiceException) {
    // Arrange
    person invalidPerson{"Max", "Mustermann"};

    EXPECT_CALL(repoMock,save_or_update(_) ).Times(0);
    EXPECT_CALL(blacklistServiceMock, isBlacklisted(invalidPerson)).WillOnce(Return(true));

    // Act + Assert
    EXPECT_THAT([&]() { objectUnderTest.speichern(invalidPerson); },ThrowsMessage<personen_service_exception>(StrEq("Unerwuensche Person")));
}
TEST_F(personen_service_impl_test,speichern__FehlerImBlacklistService__throwsPersonenServiceException) {
    // Arrange
    person invalidPerson{"Franz", "der Hunnenkoenig"};
    EXPECT_CALL(repoMock,save_or_update(_) ).Times(0);
    EXPECT_CALL(blacklistServiceMock, isBlacklisted(_)).WillOnce(Throw(std::logic_error{"xxx"}));
    // Act + Assert
    EXPECT_THAT([&]() { objectUnderTest.speichern(invalidPerson); },ThrowsMessage<personen_service_exception>(StrEq("Ein Fehler ist aufgetreten!")));
}


TEST_F(personen_service_impl_test,speichern__UnexpectedExceptionInUnderlyingService__throws_personen_service_exception) {
    // Arrange
    person validPerson{"John", "Doe"};

    EXPECT_CALL(blacklistServiceMock,isBlacklisted(_) ).WillOnce(Return(false));
    EXPECT_CALL(repoMock, save_or_update(_)).WillOnce(Throw(std::runtime_error{"upps"}));

    EXPECT_THAT([&]() { objectUnderTest.speichern(validPerson); },ThrowsMessage<personen_service_exception>(StrEq("Ein Fehler ist aufgetreten!")));
}

/*
 * Variante 1: try/catch im Test.
 *
 * Schritt fuer Schritt, ohne verschachtelte Matcher:
 *  - Act:    speichern() aufrufen und die personen_service_exception fangen.
 *            Aus ihr wird getNested() (ein std::exception_ptr) gemerkt.
 *            FAIL() stellt sicher, dass der Test scheitert, wenn gar keine
 *            Exception geworfen wird.
 *  - Assert: Der exception_ptr darf nicht leer sein. Danach wird die gemerkte
 *            Exception per std::rethrow_exception erneut geworfen und mit
 *            ThrowsMessage auf Typ (std::runtime_error) und Text ("upps") geprueft.
 *
 * Vorteil: leichter zu lesen. Nachteil: mehr Code, Ablauf steht im Test.
 * Die Variante 2 (darunter) macht dasselbe nur mit einem einzigen EXPECT_THAT.
 */
TEST_F(personen_service_impl_test,speichern__UnexpectedExceptionInUnderlyingService__nestedExceptionIsOriginalException_tryCatch) {
    // Arrange
    person validPerson{"John", "Doe"};

    EXPECT_CALL(blacklistServiceMock,isBlacklisted(validPerson) ).Times(1).WillOnce(Return(false));
    EXPECT_CALL(repoMock, save_or_update(_)).WillOnce(Throw(std::runtime_error{"upps"}));

    // Act
    std::exception_ptr nested;
    try {
        objectUnderTest.speichern(validPerson);
        FAIL() << "personen_service_exception expected";
    } catch (personen_service_exception const &e) {
        nested = e.getNested();
    }

    // Assert
    ASSERT_NE(nested, nullptr);
    EXPECT_THAT([&]() { std::rethrow_exception(nested); },ThrowsMessage<std::runtime_error>(StrEq("upps")));
}

/*
 * Variante 2: Alles in einem EXPECT_THAT.
 *
 * Ziel: Pruefen, dass die personen_service_exception die urspruengliche
 *       Exception des darunterliegenden Services als "nested" mitfuehrt.
 *
 * Der Matcher wird von aussen nach innen gelesen:
 *
 *  1. Throws<personen_service_exception>(...)
 *       Der Aufruf muss eine personen_service_exception werfen. Das Matcher-
 *       Argument bekommt die geworfene Exception und prueft sie weiter.
 *
 *  2. Property(&personen_service_exception::getNested, ...)
 *       Ruft getNested() auf der Exception auf. Das Ergebnis ist ein
 *       std::exception_ptr - also KEINE Exception, sondern nur ein "Zeiger"
 *       auf eine gespeicherte Exception.
 *
 *  3. ResultOf(rethrowNested, ...)
 *       Ein exception_ptr kann man nicht direkt mit gmock vergleichen.
 *       rethrowNested macht daraus eine Funktion, die die gespeicherte
 *       Exception per std::rethrow_exception erneut wirft.
 *
 *  4. ThrowsMessage<std::runtime_error>(StrEq("upps"))
 *       Diese Funktion muss nun eine std::runtime_error mit dem Text "upps"
 *       werfen - also genau die Exception, die der Repository-Mock geworfen hat.
 *
 * Alternative ohne Matcher-Verschachtelung: siehe der Test darueber (try/catch).
 */
TEST_F(personen_service_impl_test,speichern__UnexpectedExceptionInUnderlyingService__nestedExceptionIsOriginalException) {
    // Arrange
    person validPerson{"John", "Doe"};
    EXPECT_CALL(blacklistServiceMock,isBlacklisted(validPerson) ).Times(1).WillOnce(Return(false));
    EXPECT_CALL(repoMock, save_or_update(_)).WillOnce(Throw(std::runtime_error{"upps"}));

    // Wirft die verschachtelte Exception erneut, damit ThrowsMessage sie pruefen kann
    auto rethrowNested = [](std::exception_ptr nested) {
        return [nested]() { std::rethrow_exception(nested); };
    };

    EXPECT_THAT([&]() { objectUnderTest.speichern(validPerson); },
                Throws<personen_service_exception>(
                    Property(&personen_service_exception::getNested,
                             ResultOf(rethrowNested, ThrowsMessage<std::runtime_error>(StrEq("upps"))))));
}


TEST_F(personen_service_impl_test,speichern__HappyPath__parameterPassedToRepo){
    InSequence dummy;

    // Arrange
    person validPerson{"John", "Doe"};
    EXPECT_CALL(blacklistServiceMock,isBlacklisted(validPerson) ).Times(1).WillOnce(Return(false));
    EXPECT_CALL(repoMock,save_or_update(validPerson) ).Times(1);



    // Action

    objectUnderTest.speichern(validPerson);



}
