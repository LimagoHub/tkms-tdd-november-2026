//
// Created by JoachimWagner on 15.12.2025.
//

#pragma once


#include "gmock/gmock.h"

#include "Mockpersonen_repository.h"
#include "Mockblacklist_service.h"
#include "../../source/services/personen_service_exception.h"
#include "../../source/services/personen_service_impl.h"

using namespace testing;
class personen_service_impl_test: public Test{
protected:

    Mockpersonen_repository repoMock;
    Mockblacklist_service blacklistServiceMock;


    personen_service_impl objectUnderTest{repoMock, blacklistServiceMock};


};





