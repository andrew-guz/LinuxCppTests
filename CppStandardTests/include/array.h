#pragma once

#include "test_helper.h"

#include <array>

class Array : public TestBase
{
public:
    virtual const char* Name() const override
    {
        return "array";
    }

protected:
    virtual void TestImpl() override
    {
        std::array<int, 3> arr1 { 1, 2, 3 };
        for (const auto& i : arr1)
            Print(i);
        Print(arr1[3]);

        std::array<int, 3> arr2;
        Print(arr2[0]);
        Print(arr2[1]);

        //check how cool array initialized by 0 by default if it's partially initalized:)
        std::array<int, 3> arr3 { 1 };
        Print(arr3[0]);
        Print(arr3[1]);
    }
};
