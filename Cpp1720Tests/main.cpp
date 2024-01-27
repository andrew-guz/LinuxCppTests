#include <iostream>

#include "if_init.h"
#include "if_constexpr.h"
#include "any.h"
#include "async.h"
#include "aggregate_initialization.h"
#include "mauby_unused.h"

int main(int argc, char** argv)
{
    REGISTER_TEST(IfInit);
    REGISTER_TEST(IfConstexpr);
    REGISTER_TEST(Any);
    REGISTER_TEST(Async);
    REGISTER_TEST(AggregateInitialization);
    REGISTER_TEST(MaybeUnused);

    if (argc > 1)
        Tests::instance().RunExact(argv[1]);
    else
        Tests::instance().RunAll();

    return 0;
}
