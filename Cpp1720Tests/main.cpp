#include <iostream>

#include "if_init.h"

int main()
{
    REGISTER_TEST(IfInit);

    Tests::instance().Run();

    return 0;
}
