#pragma once

#include <iostream>

template<typename T>
std::enable_if_t<std::is_same_v<T, int>> SFINAEFunc(const T& value)
{
    std::cout << "Integer" << std::endl;
}

template<typename T>
std::enable_if_t<not std::is_same_v<T, int>> SFINAEFunc(const T& value)
{
    std::cout << "Unknown" << std::endl;
}

template<typename T>
void IfConstexprFunc(const T& value)
{
    if constexpr(std::is_same_v<T, int>)
        std::cout << "Integer" << std::endl;
    else
        std::cout << "Unknown" << std::endl;
}
