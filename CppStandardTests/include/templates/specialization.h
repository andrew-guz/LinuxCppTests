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
