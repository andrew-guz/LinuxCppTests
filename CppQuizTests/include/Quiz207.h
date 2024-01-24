#pragma once

#include "QuizHelper.h"

#include <map>

QUIZ(207)
    //creating new map item it will be initialized with default ctor or 0
    std::map<int, int> m;
    std::cout << m[42] << std::endl;

    int i;
    std::cout << i << std::endl;

    std::map<int, double> m2;
    std::cout << m2[42] << std::endl;
    std::map<int, int*> m3;
    std::cout << m3[42] << std::endl;
    std::map<int, EmptyClass> m4;
    auto& ec = m4[42];
    std::map<int, NoDefaultCtor> m5;
    //auto& ndc = m5[42];
QUIZ_END
