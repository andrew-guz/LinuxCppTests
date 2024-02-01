#pragma once

#include "test_helper.h"

class IfConstexpr : public TestBase
{
public:
    virtual const char* Name() const override
    {
        return "if constexpr";
    }

protected:
    template<typename T>
    static void print(const T& value)
    {
        if constexpr (std::is_same_v<T, int>)
            Print("is int");
        else if constexpr (std::is_same_v<T, bool>)
            Print("is bool");
        else if constexpr (std::is_same_v<T, char*>)
            Print("is char*");
        else if constexpr (std::is_pointer_v<T>)
            Print("is pointer");
        else
            Print("not supported type");
    }

    virtual void TestImpl() override
    {
        print(5);
        print(false);
        print("Some chars");
        auto text = "Some chars";
        print(text);
    }
};
