#pragma once

#include <iostream>

#include "TestClasses.h"

#define QUIZ(x) void Quiz##x() \
{ \
    std::cout << std::endl << "----" << #x << "----" << std::endl;

#define QUIZ_END \
    std::cout << std::endl << "--------" << std::endl; \
}
