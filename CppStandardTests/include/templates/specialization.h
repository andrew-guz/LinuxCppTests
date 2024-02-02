#pragma once

#include <string>
#include <iostream>

template<typename T>
void SpecialPrint(const T& value)
{
    std::cout << value << std::endl;
}

template<>
void SpecialPrint(const std::string& value)
{
    std::cout << "'" << value << "'" << std::endl;
}

class SpecialPrintClassWithTemplateFunction
{
public:
    template<typename T>
    static void SpecialPrint(const T& value)
    {
        std::cout << value << std::endl;
    }   
};

template<>
void SpecialPrintClassWithTemplateFunction::SpecialPrint(const std::string& value)
{
    std::cout << "'" << value << "'" << std::endl;
}

template<typename T>
class SpecialPrintTemplateClass
{
public:    
    static void SpecialPrint(const T& value)
    {
        std::cout << value << std::endl;
    }   
};

template<>
void SpecialPrintTemplateClass<std::string>::SpecialPrint(const std::string& value)
{
    std::cout << "'" << value << "'" << std::endl;
}
