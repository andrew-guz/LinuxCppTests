#pragma once

#include "test_helper.h"

#include "templates/variadic.h"
#include "templates/specialization.h"
#include "templates/using.h"
#include "templates/folding.h"
#include "templates/sfinae_vs_if_constexpr.h"

#include <string>
using namespace std::string_literals;

class Templates : public TestBase
{
public:
    virtual const char* Name() const override
    {
        return "templates";
    }

protected:
    virtual void TestImpl() override
    {
        Print(1, true, std::string{ "some string"});

        SpecialPrint(1);
        SpecialPrint(true);
        SpecialPrint("hello");
        SpecialPrint(std::string{"hello"});

        SpecialPrintClassWithTemplateFunction::SpecialPrint(1);
        SpecialPrintClassWithTemplateFunction::SpecialPrint(true);
        SpecialPrintClassWithTemplateFunction::SpecialPrint("hello");
        SpecialPrintClassWithTemplateFunction::SpecialPrint(std::string{"hello"});

        SpecialPrintTemplateClass<int>::SpecialPrint(1);
        SpecialPrintTemplateClass<bool>::SpecialPrint(true);
        SpecialPrintTemplateClass<const char*>::SpecialPrint("hello");
        SpecialPrintTemplateClass<std::string>::SpecialPrint(std::string{"hello"});

        //example of template class deduction
        SpecialPrintTemplateClass sptc1(1);
        sptc1.SpecialPrint();

        [[maybe_unused]] CharArray<5> charArray1 = { 'a', 'b', 'c', 'd', 0 };
        Print(charArray1.data());

        //check how cool array initialized by 0 by default :)
        [[maybe_unused]] CharArray<5> charArray2 = { 'a', 'b', 'c', 'd' };
        Print(charArray2.data());

        auto sum1 = Sum(1, 2, 3);
        PrintInOneLine("1+2+3=", sum1);

        PrintWithSpaces(1, 2.0, "hello");

        SFINAEFunc1("hello"s);
        SFINAEFunc1(1);
        SFINAEFunc1(0.6);
        SFINAEFunc2("hello"s);
        SFINAEFunc2(1);
        SFINAEFunc2(0.6);

        IfConstexprFunc("hello"s);
        IfConstexprFunc(1);
        IfConstexprFunc(0.6);
    }
};
