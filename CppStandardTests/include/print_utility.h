#pragma once

#include <iostream>

void Print()
{
    std::cout << std::endl;
}

template<typename T, typename ...Types>
void Print(const T& first, const Types& ...args)
{
    std::cout << first;
    if constexpr (sizeof...(args) > 0)
        std::cout << ", ";
    Print(args...);
}
