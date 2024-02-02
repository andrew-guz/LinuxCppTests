#pragma once

#include "test_helper.h"

#include "templates/print.h"
#include "templates/specialization.h"

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
    }
};
