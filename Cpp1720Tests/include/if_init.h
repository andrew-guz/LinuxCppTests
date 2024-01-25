#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

void TestIfInit()
{
    std::vector v {1,2,3,4};
    if (auto i = std::find(v.begin(), v.end(), 2); i != v.end())
    {
        std::cout << "1";
    }
    else
    {
        if (i == v.end())
            std::cout << "2";
    }
}
