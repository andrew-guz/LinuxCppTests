#pragma once

#include "QuizHelper.h"

/*
Hack here is in decltype
decltype(a) => int
decltype((a)) => int&
*/
QUIZ(38)
    int a = 0;
    decltype((a)) b = a;
    b++;
    std::cout << a << b << std::endl;
QUIZ_END