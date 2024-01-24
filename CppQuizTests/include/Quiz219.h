#pragma once

#include "QuizHelper.h"

template<typename T>
T sum(T arg) {
    return arg;   
}

template<typename T, typename ...Args>
T sum(T arg, Args... args) {    
    return arg + sum<T>(args...);
}

/*
  in sum<T> = a1 + sum<T>() T is already known.
  for n1 it is double
  for n2 it is int
  int i = 0.5; i == 0
*/

QUIZ(219)
    auto n1 = sum(0.5, 1, 0.5, 1);
    auto n2 = sum(1, 0.5, 1, 0.5);
    std::cout << n1 << n2 << std::endl;
QUIZ_END