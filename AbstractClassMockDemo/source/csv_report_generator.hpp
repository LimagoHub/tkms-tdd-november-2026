#pragma once

#include <string>
#include <vector>

#include "report_generator.hpp"

// Eine konkrete Unterklasse fuer die Anwendung (main.cpp).
// Fuer den Test der Basisklasse wird sie NICHT gebraucht.
class CsvReportGenerator : public ReportGenerator {
public:
	explicit CsvReportGenerator(std::vector<std::string> rows);

protected:
	bool hasData() const override;
	std::string header() override;
	std::string body() override;

private:
	std::vector<std::string> rows_;
};
