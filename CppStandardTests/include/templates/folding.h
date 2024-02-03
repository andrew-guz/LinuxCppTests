#pragma once

template<typename T, typename ...Types>
auto Sum(const T& first, const Types& ... args)
{
    return (first + ... + args);
}
