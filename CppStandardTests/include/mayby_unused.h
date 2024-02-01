#pragma once

#include "test_helper.h"

/*
Good example:
int i = 0;
assert(i > 0);
in Debug assert will be used and everything is OK
but in Release assert will not be compiled and warning will appear
To prevent warning in Release use [[maybe_unused]] attribute
*/

class MaybeUnused : public TestBase
{
public:
    virtual const char* Name() const override
    {
        return "maybe unused";
    }

protected:
    virtual void TestImpl() override
    {
        [[maybe_unused]] int i = 0;
    }
};
