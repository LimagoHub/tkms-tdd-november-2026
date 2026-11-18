#pragma once

#include <string>
#include <utility>

// Abstrakte Basisklasse (Template-Method-Pattern):
// generate() ist konkret und enthaelt die Logik, die wir testen wollen.
// header(), body() und hasData() sind die abstrakten "Hooks" fuer die Unterklassen.
class ReportGenerator {
public:
	explicit ReportGenerator(std::string footer) : footer_(std::move(footer)) {}
	virtual ~ReportGenerator() = default;

	std::string generate();

protected:
	virtual bool hasData() const = 0;
	virtual std::string header() = 0;
	virtual std::string body() = 0;

private:
	std::string footer_;
};
