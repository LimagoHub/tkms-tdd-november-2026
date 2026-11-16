//
// Created by JoachimWagner on 16.11.2026.
//

#pragma once

#include "Dependency.h"
#include <algorithm>

class MyServiceUsingDependency {

    IDependency &dependency;

public:
    explicit MyServiceUsingDependency(IDependency &dependency)
        : dependency(dependency) {
    }

    /*
     *  1. Foo wird mit kardinalität 1 aufgerufen
     *  2. Parameter wurde in Grossbuchstaben gewandelt
     *  3. korrekter call mit richtigem parameter
     *
     */
    void f(std::string value) {
        transform(value.begin(), value.end(), value.begin(), ::toupper);
        dependency.foo(value);


    }

    /*
     *
     *
     */
    size_t g(std::string value) {
        value += " Welt";

        return dependency.foobar(value) + 5;
    }

    long h() {
        const auto barValue = dependency.bar();
        return barValue * barValue;

    }

};
