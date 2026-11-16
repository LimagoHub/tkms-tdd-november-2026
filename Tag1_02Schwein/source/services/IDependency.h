//
// Created by JoachimWagner on 16.11.2026.
//

#pragma once
#include <string>


class IDependency {
public:
    IDependency() = default;
    virtual ~IDependency() = default;

    virtual void foo(std::string message )const  = 0;

    virtual int bar( )const  = 0;

    virtual size_t foobar(std::string message )const  = 0;

};
