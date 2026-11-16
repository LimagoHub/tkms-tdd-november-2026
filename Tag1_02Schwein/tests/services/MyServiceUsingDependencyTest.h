//
// Created by JoachimWagner on 16.11.2026.
//


#pragma once
//#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockDependency.h"
#include "../../source/services/MyServiceUsingDependency.h"
using namespace testing;

class MyServiceUsingDependencyTest :public Test{
protected:
    MockDependency dependencyMock;
    MyServiceUsingDependency objectUnderTest{dependencyMock};
};
