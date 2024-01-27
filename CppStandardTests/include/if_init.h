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
            std::cout << "1" << std::endl;
        else if (i == v.end())
            std::cout << "2" << std::endl;

        if (auto i = std::find(v.begin(), v.end(), 5); i != v.end())
            std::cout << "1" << std::endl;
        else if (i == v.end())
            std::cout << "2" << std::endl;
    }
};
