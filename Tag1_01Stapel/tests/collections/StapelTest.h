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
};
