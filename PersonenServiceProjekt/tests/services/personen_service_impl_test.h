//
// Created by JoachimWagner on 15.12.2025.
//

#pragma once

#include "Mockpersonen_repository.h"
#include "gmock/gmock.h"


#include "../../source/services/personen_service_exception.h"
#include "../../source/services/personen_service_impl.h"

using namespace testing;
class personen_service_impl_test: public Test{
protected:

    Mockpersonen_repository repoMock;

    personen_service_impl objectUnderTest{repoMock};


};





