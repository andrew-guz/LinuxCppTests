#pragma once

#include "QuizHelper.h"

/*template <typename T>
struct A {
    static_assert(false);
};*/

/*
Undefined
theoretically static_assert(false) should fail during compilation
on the ohter hand why compile not used template
*/

QUIZ(244)
    std::cout << 1 << std::endl;
QUIZ_END