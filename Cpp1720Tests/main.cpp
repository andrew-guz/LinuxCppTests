#include <iostream>

#include "if_init.h"
#include "if_constexpr.h"
#include "any.h"

int main()
{
    REGISTER_TEST(IfInit);
    REGISTER_TEST(IfConstexpr);
    REGISTER_TEST(Any);

    Tests::instance().Run();

    return 0;
}
