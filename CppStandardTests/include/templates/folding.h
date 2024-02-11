#pragma once

#include <iostream>

template<typename T, typename ...Types>
auto Sum(const T& first, const Types& ... args)
{
    return (first + ... + args);
}

template<typename T, typename ...Types>
void PrintInOneLine(const T& first, const Types& ...args)
{
    std::cout << first;
    auto addNext = [](const auto& arg)
    {
        std::cout << arg;
    };
    (..., addNext(args));
    std::cout << std::endl;
}


template<typename T, typename ...Types>
void PrintWithSpaces(const T& first, const Types& ...args)
{
    std::cout << first;
    auto addNext = [](const auto& arg)
    {
        std::cout << " " << arg;
    };
    (..., addNext(args));
    std::cout << std::endl;
}
