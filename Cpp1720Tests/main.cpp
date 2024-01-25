#include <iostream>

#include "if_init.h"
#include "if_constexpr.h"

int main()
{
    REGISTER_TEST(IfInit);
    REGISTER_TEST(IfConstexpr);

    Tests::instance().Run();

    return 0;
}
