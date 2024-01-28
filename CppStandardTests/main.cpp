#include <iostream>

#include "if_init.h"
#include "if_constexpr.h"
#include "any.h"
#include "async.h"
#include "aggregate_initialization.h"
#include "mayby_unused.h"
#include "nodiscard.h"
#include "user_defined_literals.h"

int main(int argc, char** argv)
{
    REGISTER_TEST(IfInit);
    REGISTER_TEST(IfConstexpr);
    REGISTER_TEST(Any);
    REGISTER_TEST(Async);
    REGISTER_TEST(AggregateInitialization);
    REGISTER_TEST(MaybeUnused);
    REGISTER_TEST(Nodiscard);
    REGISTER_TEST(UserDefinedLiterals);

    if (argc > 1)
        Tests::instance().RunExact(argv[1]);
    else
        Tests::instance().RunAll();

    return 0;
}
