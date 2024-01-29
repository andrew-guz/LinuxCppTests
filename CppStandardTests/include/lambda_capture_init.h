#pragma once

#include "test_helper.h"

namespace LambdaCaptureInitTest
{
    int f(int x)
    {
        return x * 2;
    }
};


class LambdaCaptureInit : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "lambda capture init";
    }

protected:
    virtual void TestImpl() override
    {
        auto lambda = [y = LambdaCaptureInitTest::f(5)]{ return y; };
        auto lambdaValue = lambda();
        Print(lambdaValue);
    }
};
