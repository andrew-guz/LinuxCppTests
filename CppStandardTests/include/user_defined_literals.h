#pragma once

#include "test_helper.h"

/*
Attention. There is limited list of types used for ()
Return value can be any.
*/
long double operator""_km(long double km)
{
    return km * 1000.0;
}

long double operator""_m(long double m)
{
    return m;
}

long double operator""_cm(long double cm)
{
    return cm * 0.01;
}

size_t operator"" _strlen(const char* str, size_t length)
{
    return std::strlen(str);
}

class UserDefinedLiterals : public TestBase
{
public:
    virtual const char* Name() const override
    {
        return "user defined literals";
    }

protected:
    virtual void TestImpl() override
    {
        Print(50.0_km, 50.0_m, 50.0_cm);
        Print("Hello World!"_strlen);
    }
};
