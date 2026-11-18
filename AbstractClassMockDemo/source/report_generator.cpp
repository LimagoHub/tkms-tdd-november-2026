#include "report_generator.hpp"

std::string ReportGenerator::generate() {
	if (!hasData()) {
		return "Keine Daten\n" + footer_;
	}
	// Bewusst in getrennten Anweisungen: bei header() + body() in EINEM Ausdruck
	// ist die Aufrufreihenfolge nicht festgelegt (GCC ruft body() zuerst auf).
	std::string result = header();
	result += "\n";
	result += body();
	result += "\n";
	result += footer_;
	return result;
}
