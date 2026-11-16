//
// Created by JoachimWagner on 16.11.2026.
//

#pragma once

#include <iostream>

#include "IDependency.h"
class Dependency: public IDependency {

public:
    void foo(std::string message) const override {
        std::cout << message << std::endl;
    }

    int bar() const override {
        return 42;
    }

    size_t foobar(std::string message) const override {
        return message.length();
    }
};
