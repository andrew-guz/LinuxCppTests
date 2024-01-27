#pragma once

#include "test_helper.h"

namespace NodiscardTest
{
    [[nodiscard]] int checkSomething()
    {
        return -1;
    }

    struct [[nodiscard]] ErrorDescription
    {
        int _code;
        std::string _message;
    };

    ErrorDescription checkAnotherThing()
    {
        return { -1, "some error" };
    }
};

class Nodiscard : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "nodiscard";
    }

protected:
    virtual void TestImpl() override
    {
        NodiscardTest::checkSomething();
        NodiscardTest::checkAnotherThing();
    }
};
