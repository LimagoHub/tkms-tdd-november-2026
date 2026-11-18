#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "myservice_using_dependency_test.h"

/*
 *
 *
 *
Das Problem

my_service_using_dependency benutzt dependency_to_fake direkt, als Wert-Member (dependency_to_fake dependency_;). Es gibt kein Interface und keine Dependency Injection. Außerdem ist get_lastname() statisch. Du kannst die Abhängigkeit also nicht per Konstruktor austauschen, und gMock kann eine solche Klasse nicht ableiten, um ein Mock-Objekt einzuschleusen.

Die Lösung: Link-Time Substitution mit einer Weiche

Der Trick hat drei Teile.

1. Die echte Implementierung wird im Testprojekt nicht gelinkt.
In tests/CMakeLists.txt stehen nur main.cpp, myservice_using_dependency_test.cpp und globaltest.cpp. Die Datei dependecy_to_fake.cpp mit den echten Methoden ("John", "Doe", value*value) fehlt dort.

Der Linker braucht aber Definitionen für dependency_to_fake::get_firstname(), get_lastname() und calculate(). Diese Definitionen liefert der Test selbst (myservice_using_dependency_test.cpp:43-58). Das ist die Link-Time Substitution: Der Linker nimmt die Test-Variante statt der echten, und der Produktionscode (my_service_using_dependency.h) bleibt unverändert.

2. Der Mock ist ein normales gMock-Objekt.
dependency_to_fake_mock (Header, Zeile 8-14) hat dieselben drei Methoden per MOCK_METHOD. Es hat aber keine Beziehung zur echten Klasse und erbt nicht von ihr. Es dient nur dazu, EXPECT_CALL und Return zu nutzen.

3. current_thread_mock verbindet beides.
thread_local dependency_to_fake_mock* current_thread_mock = nullptr;
Das ist ein globaler Zeiger auf den aktuell aktiven Mock. Die Ersatz-Implementierungen leiten Aufrufe an ihn weiter:
std::string dependency_to_fake::get_firstname() const {
    if (current_thread_mock) return current_thread_mock->get_firstname();
    return "Default Legacy Name";
}

Ablauf eines Tests

SetUp():     current_thread_mock = &dMock;     // Zeiger auf Mock der Testinstanz

Test:        EXPECT_CALL(dMock, get_firstname()).WillOnce(Return("Fritz"));
             object_under_test.first_method_under_test()
               └─> dependency_.get_firstname()          // Aufruf der "echten" Klasse
                     └─> (Test-Ersatzimplementierung)
                           └─> current_thread_mock->get_firstname()   // landet im gMock
                                 └─> liefert "Fritz"
             Ergebnis: "Fritz Hallo"

TearDown():  current_thread_mock = nullptr;    // Aufräumen

Warum diese Konstruktion?

- Warum ein Zeiger? Die freien Ersatzfunktionen und die statische Methode haben keinen Zugriff auf this der Testfixture. Sie brauchen einen globalen Anker, um den Mock zu finden. Deshalb funktioniert das auch bei static get_lastname().
- Warum thread_local? Jeder Thread hat seine eigene Kopie des Zeigers. Tests, die parallel in mehreren Threads laufen, überschreiben sich . Bei streng sequentiellen Tests wäre ein normaler globaler Zeiger auch ausreichend. thread_local ist die sichere Variante.
- Warum in SetUp/TearDown setzen und löschen? dMock lebt nur so lange wie die Fixture-Instanz, also einen Test lang. Würde der Zeiger danach stehen bleiben, wäre er ein Dangling Pointer. Ein späterer Aufruf der Ersatzfunktionen würde dann auf zerstörten Speicher zugreifen. Mit nullptr greift stattdessen der Fallback ("Default Legacy Name").
- Warum die Fallback-Werte? Wird die Ersatzfunktion außerhalb eines Tests aufgerufen (z. B. in einem statischen Initialisierer), crasht nichts.
 *
 *
 *
 */


// current_thread_mock (thread-lokaler Pointer auf den Mock) ist im Header als inline definiert.

TEST_F(myservice_using_dependency_test, FirstMethod) {
	EXPECT_CALL(dMock, get_firstname()).WillOnce(::testing::Return("Fritz"));

	EXPECT_EQ(object_under_test.first_method_under_test(), "Fritz Hallo");
}

using ::testing::Return;

TEST_F(myservice_using_dependency_test, ShouldReturnMockedName) {


	// 2. Erwartung definieren
	EXPECT_CALL(dMock, get_lastname())
		.WillOnce(Return("Skywalker"));




	// 4. Aufruf der statischen/freien Funktion
	std::string result = dependency_to_fake::get_lastname();

	// 5. Assert
	EXPECT_EQ(result, "Skywalker");


}

/*
 * Linker-Sidetracking (oder Link-Time Subsitution) nutzen, um Legacy Code zu baendigen, der keine Interfaces nutzt.
 *
 */
// Implementierung der Legacy-Methoden
std::string dependency_to_fake::get_firstname() const {
	if (current_thread_mock) return current_thread_mock->get_firstname();
	return "Default Legacy Name";
}

long dependency_to_fake::calculate(const int value) const {
	if (current_thread_mock) return current_thread_mock->calculate(value);
	return 0;
}

// ACHTUNG: Statische Methoden können keine Member-Mocks einfach so nutzen
// Hier musst du den Mock ebenfalls über den TLS-Pointer ansprechen
string dependency_to_fake::get_lastname() {
	if (current_thread_mock) return current_thread_mock->get_lastname();
	return "Default Doe";
}

