#include "csv_report_generator.hpp"

#include <utility>

CsvReportGenerator::CsvReportGenerator(std::vector<std::string> rows)
	: ReportGenerator("--- Ende ---"), rows_(std::move(rows)) {}

bool CsvReportGenerator::hasData() const {
	return !rows_.empty();
}

std::string CsvReportGenerator::header() {
	return "name;wert";
}

std::string CsvReportGenerator::body() {
	std::string result;
	for (std::size_t i = 0; i < rows_.size(); ++i) {
		if (i > 0) result += "\n";
		result += rows_[i];
	}
	return result;
}
