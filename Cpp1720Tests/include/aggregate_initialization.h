#pragma once

#include "test_helper.h"

/*
Pay attention that ordinal initialization (uniform) {} will set property to 0.
cppref:
If T is a scalar type, the object is initialized to the value obtained by explicitly converting the integer literal ​0​ (zero) to T.
*/

namespace AggregateInitializationTest
{
    struct A
    {
        int i;
    };

    struct B : A
    {
        float f;
    };
};

class AggregateInitialization : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "aggregate initialization";
    }

protected:
    virtual void TestImpl() override
    {
        AggregateInitializationTest::A a1 {};
        PRINT(a1.i);

        AggregateInitializationTest::B b1 {};
        PRINT(b1.i);
        PRINT(b1.f);

        AggregateInitializationTest::B b2 {{}};
        PRINT(b2.i);
        PRINT(b2.f);

        AggregateInitializationTest::B b3 {{}, 10.0f};
        PRINT(b3.i);
        PRINT(b3.f);

        AggregateInitializationTest::B b4 {{42}, 12.0f};
        PRINT(b4.i);
        PRINT(b4.f);
    }
};
