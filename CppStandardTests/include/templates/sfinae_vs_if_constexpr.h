#pragma once

#include <iostream>

template<typename T>
std::enable_if_t<std::is_same_v<T, int>> SFINAEFunc1(const T& value)
{
    std::cout << "Integer" << std::endl;
}

template<typename T>
std::enable_if_t<std::is_same_v<T, std::string>> SFINAEFunc1(const T& value)
{
    std::cout << "String" << std::endl;
}

template<typename T>
std::enable_if_t<not std::is_same_v<T, int> and not std::is_same_v<T, std::string>> SFINAEFunc1(const T& value)
{
    std::cout << "Unknown" << std::endl;
}

template<typename T>
std::enable_if_t<std::is_same_v<T, int>> SFINAEFunc2(const T& value)
{
    std::cout << "Integer" << std::endl;
}

template<typename T>
std::enable_if_t<std::is_same_v<T, std::string>> SFINAEFunc2(const T& value)
{
    std::cout << "String" << std::endl;
}

//the less preferred function during compiler searching 
void SFINAEFunc2(...)
{
    std::cout << "Unknown" << std::endl;
}

template<typename T>
void IfConstexprFunc(const T& value)
{
    if constexpr(std::is_same_v<T, int>)
        std::cout << "Integer" << std::endl;
    else if constexpr(std::is_same_v<T, std::string>)
        std::cout << "String" << std::endl;
    else
        std::cout << "Unknown" << std::endl;
}
