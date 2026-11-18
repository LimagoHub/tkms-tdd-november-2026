#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "report_generator.hpp"

using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;

// Test-Unterklasse: macht die abstrakte Klasse instanziierbar.
// Die pure-virtual Hooks werden mit gMock gemockt.
// (protected Methoden duerfen im Mock unter public stehen.)
class MockReportGenerator : public ReportGenerator {
public:
	using ReportGenerator::ReportGenerator;  // erbt den Konstruktor mit footer

	MOCK_METHOD(bool, hasData, (), (const, override));
	MOCK_METHOD(std::string, header, (), (override));
	MOCK_METHOD(std::string, body, (), (override));
};

class ReportGeneratorTest : public ::testing::Test {
protected:
	MockReportGenerator objectUnderTest{"--- Ende ---"};
};

TEST_F(ReportGeneratorTest, generate_withData_combinesHeaderBodyAndFooter) {
	EXPECT_CALL(objectUnderTest, hasData()).WillOnce(Return(true));
	EXPECT_CALL(objectUnderTest, header()).WillOnce(Return("Titel"));
	EXPECT_CALL(objectUnderTest, body()).WillOnce(Return("Inhalt"));

	EXPECT_EQ("Titel\nInhalt\n--- Ende ---", objectUnderTest.generate());
}

TEST_F(ReportGeneratorTest, generate_withoutData_doesNotCallHeaderOrBody) {
	EXPECT_CALL(objectUnderTest, hasData()).WillOnce(Return(false));
	EXPECT_CALL(objectUnderTest, header()).Times(0);
	EXPECT_CALL(objectUnderTest, body()).Times(0);

	EXPECT_EQ("Keine Daten\n--- Ende ---", objectUnderTest.generate());
}

TEST_F(ReportGeneratorTest, generate_callsHooksInOrder) {
	InSequence seq;  // Erwartungen muessen in dieser Reihenfolge erfuellt werden
	EXPECT_CALL(objectUnderTest, hasData()).WillOnce(Return(true));
	EXPECT_CALL(objectUnderTest, header()).WillOnce(Return(""));
	EXPECT_CALL(objectUnderTest, body()).WillOnce(Return(""));

	objectUnderTest.generate();
}

// Variante mit NiceMock + ON_CALL: nur Default-Verhalten, keine Aufruf-Erwartungen.
TEST(ReportGeneratorNiceMockTest, generate_usesFooterFromConstructor) {
	NiceMock<MockReportGenerator> generator{"Seite 1"};
	ON_CALL(generator, hasData()).WillByDefault(Return(true));
	ON_CALL(generator, header()).WillByDefault(Return("H"));
	ON_CALL(generator, body()).WillByDefault(Return("B"));

	EXPECT_EQ("H\nB\nSeite 1", generator.generate());
}
