//
// Created by JoachimWagner on 16.11.2026.
//

#pragma once

#include "IDependency.h"
class ToDelete : public IDependency{
public:
    void foo(std::string message) const override {

    }

    int bar() const override {
        return 0;
    }

    size_t foobar(std::string message) const override {
        return 0;
    }
};
