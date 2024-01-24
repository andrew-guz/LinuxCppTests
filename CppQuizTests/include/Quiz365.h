#pragma once

#include "QuizHelper.h"

/*
  Correct answer - undefined. Depends on size of int and short.
  unsigned short has conversion rank lower than int (§[conv.rank]) and so gets converted to int
  unsigned short a = zero - one; a = 65535
  auto a = zero - one; a = -1; treated as int!
*/
QUIZ(365)
  unsigned short zero = 0, one = 1;
  if (zero - one < zero)
    std::cout << "less" << std::endl;
  else
    std::cout << "more" << std::endl;
QUIZ_END