#include <iostream>

#include "if_init.h"
#include "if_constexpr.h"
#include "any.h"
#include "async.h"

int main()
{
    REGISTER_TEST(IfInit);
    REGISTER_TEST(IfConstexpr);
    REGISTER_TEST(Any);
    REGISTER_TEST(Async);

    Tests::instance().Run();

    return 0;
}
