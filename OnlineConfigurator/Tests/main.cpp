#include <iostream>

#include "Uuid.h"

int main()
{
    Uuid id;
    std::cout << id.data() << std::endl;

    return 0;
}
