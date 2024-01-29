#pragma once

#include "test_helper.h"

#include <any>
#include <string>

namespace AnyTest
{
    class A
    {
    private:
        std::string _value;
    };
};

class Any : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "any";
    }

protected:
    template<typename T>
    T convert(const std::any& a)
    {
        try
        {
            auto value = std::any_cast<T>(a);
            return value;
        }
        catch(...)
        {
            //wanted to apply ""s but due to headers and chrono s treated as seconds
            Print(std::string{"No conversion to "} + typeid(T).name());
            return {};
        }
    }

    virtual void TestImpl() override
    {
        std::any a1;
        Print(a1.has_value());
        a1 = 5;
        Print(a1.has_value());
        auto i = std::any_cast<int>(a1);
        Print(i);
        convert<std::string>(a1);
        convert<float>(a1);        
        a1 = "Hello";
        convert<std::string>(a1);
        a1.reset();
        Print(a1.has_value());

        int i2 = 10;
        std::any a2 {&i2};
        Print(i2);
        Print(*std::any_cast<int*>(a2));
        (*std::any_cast<int*>(a2)) = 11;
        Print(i2);
        Print(*std::any_cast<int*>(a2));

        AnyTest::A a_obj;
        std::any a3 {a_obj};
        Print(a3.has_value());
        [[maybe_unused]] auto a_obj2 = std::any_cast<AnyTest::A>(a3);
    }
};
