#pragma once

#include "test_helper.h"

#include <variant>

using namespace std::string_literals;

class UseVariant : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "variant";
    }

protected:
    virtual void TestImpl() override
    {
        std::variant<int, bool, std::string> v1 = { 5 };
        Print(std::get<int>(v1));
        Print(std::get<0>(v1));
        try
        {
            Print(std::get<bool>(v1));
        }
        catch(const std::exception& e)
        {
            Print("Can't get bool because right now v1 contains int");
        }
        Print(std::get_if<bool>(&v1) ? "Bool found" : "No bool");
        v1 = "Test string"s;
        Print(std::get<std::string>(v1));
        Print(std::get<2>(v1));

        auto visitFunction = [](auto& a)
        {
            using T = std::decay_t<decltype(a)>;
            if constexpr(std::is_same_v<T, bool>)
                Print("Visiting bool");
            else if constexpr(std::is_same_v<T, int>)
                Print("Visiting int");
            else
                Print("Visiting failed");
        };
        std::variant<bool, int> v2;
        std::visit(visitFunction, v2);
        v2 = 45;
        std::visit(visitFunction, v2);
        v2 = true;
        std::visit(visitFunction, v2);
    }
};
