//
// Created by JoachimWagner on 16.11.2026.
//


#pragma once
//#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <memory>
#include <utility>
#include "MockDependency.h"
#include "../../source/services/MyServiceUsingDependency.h"
using namespace testing;

class MyServiceUsingDependencyTest :public Test{
protected:
    // Reihenfolge ist wichtig (Initialisierung in Deklarationsreihenfolge):
    // 1. Mock erzeugen, 2. nicht-besitzende Referenz darauf merken,
    // 3. Eigentum per std::move an das Objekt under Test abgeben.
    std::unique_ptr<MockDependency> mockOwner{std::make_unique<MockDependency>()};
    MockDependency &dependencyMock{*mockOwner};
    MyServiceUsingDependency objectUnderTest{std::move(mockOwner)};
};
