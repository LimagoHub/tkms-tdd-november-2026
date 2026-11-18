#include <iostream>

#include "csv_report_generator.hpp"

int main() {
	CsvReportGenerator generator({"a;1", "b;2"});
	std::cout << generator.generate() << std::endl;
}
