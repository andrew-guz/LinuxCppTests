#pragma once

#include "test_helper.h"

class IfConstexpr : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "if constexpr";
    }

protected:
    template<typename T>
    static void print(const T& value)
    {
        if constexpr (std::is_same_v<T, int>)
            std::cout << "is int" << std::endl;
        else if constexpr (std::is_same_v<T, bool>)
            std::cout << "is bool" << std::endl;
        else if constexpr (std::is_same_v<T, char*>)
            std::cout << "is char*" << std::endl;
        else if constexpr (std::is_pointer_v<T>)
            std::cout << "is pointer" << std::endl;
        else
            std::cout << "not supported type" << std::endl;
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
