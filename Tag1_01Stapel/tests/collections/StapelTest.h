//
// Created by JoachimWagner on 16.11.2026.
//

#pragma once
#include "gmock/gmock.h"


#include "../../source/collections/Stapel.h"
#include "../../source/collections/StapelException.h"

using namespace testing;

class StapelTest :public Test{
protected:
    Stapel objectUnderTest ;

    auto fillUpToLimit()-> void {
        for (int i = 0; i < 10; i++) {
            EXPECT_NO_THROW(objectUnderTest.push(1));
        }
    }
};
