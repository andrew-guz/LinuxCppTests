#pragma once

#include "test_helper.h"

namespace StructureBindingTest
{
    struct A
    {
        int x;
        int y;
    };
};

class StructureBinding : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "structure binding";
    }

protected:
    virtual void TestImpl() override
    {
        auto [i, j] = GetPair();
        PRINT(i << ", " << j);
        auto [b, s, a_ptr] = GetTuple();
        PRINT(b << ", " << s << ", " << a_ptr->x << ", " << a_ptr->y);
    }

private:
    static std::pair<int, int> GetPair()
    {
        return std::make_pair(1, 2);
    }

    static std::tuple<bool, std::string, std::shared_ptr<StructureBindingTest::A>> GetTuple()
    {
        return std::make_tuple(false, "Hello", std::make_shared<StructureBindingTest::A>(5, 6));
    }
};
