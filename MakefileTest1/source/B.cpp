#include "B.h"

#include "A.h"

void B::callA(const std::string& text)
{
    A().print(text);
}
