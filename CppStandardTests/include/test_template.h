#pragma once

#include "test_helper.h"

class NAME : public TestBase
{
public:
    virtual const char* Name() const override
    {
        return "NAME";
    }

protected:
    virtual void TestImpl() override
    {

    }
};
