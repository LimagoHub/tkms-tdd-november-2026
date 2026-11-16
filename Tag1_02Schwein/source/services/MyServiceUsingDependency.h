//
// Created by JoachimWagner on 16.11.2026.
//

#pragma once

#include "Dependency.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>

class MyServiceUsingDependency {

    std::unique_ptr<IDependency> dependency_;

public:
    // Sink-Parameter: Der Aufrufer muss das Eigentum explizit abgeben (std::move).
    explicit MyServiceUsingDependency(std::unique_ptr<IDependency> dependency)
        : dependency_(std::move(dependency)) {
        if (!dependency_) throw std::invalid_argument("Dependency darf nicht nullptr sein!");
    }

    /*
     *  1. Foo wird mit kardinalität 1 aufgerufen
     *  2. Parameter wurde in Grossbuchstaben gewandelt
     *  3. korrekter call mit richtigem parameter
     *
     */
    void f(std::string value) {
        transform(value.begin(), value.end(), value.begin(), ::toupper);
        dependency_->foo(value);


    }

    /*
     *
     *
     */
    size_t g(std::string value) {
        value += " Welt";

        return dependency_->foobar(value) + 5;
    }

    long h() {
        const auto barValue = dependency_->bar();
        return barValue * barValue;

    }

};
