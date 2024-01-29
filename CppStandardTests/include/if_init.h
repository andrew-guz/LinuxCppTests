#pragma once

#include "test_helper.h"

#include <iostream>
#include <algorithm>
#include <vector>

class IfInit final : public TestBase
{
public:
    virtual const char* Name() const override
    {
        return "if initialization";
    }

protected:
    virtual void TestImpl() override
    {
        std::vector v {1,2,3,4};
        if (auto i = std::find(v.begin(), v.end(), 2); i != v.end())
            Print("2 found");
        else if (i == v.end())
            Print("2 not found");

        if (auto i = std::find(v.begin(), v.end(), 5); i != v.end())
            Print("5 found");
        else if (i == v.end())
            Print ("5 not found");
    }
};
