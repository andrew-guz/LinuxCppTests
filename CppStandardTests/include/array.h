#pragma once

#include "test_helper.h"

#include <array>

class Array : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "array";
    }

protected:
    virtual void TestImpl() override
    {
        std::array<int, 3> arr1 { 1, 2, 3 };
        for (const auto& i : arr1)
            std::cout << i << std::endl;
        std::cout << arr1[3] << std::endl;
    }
};
