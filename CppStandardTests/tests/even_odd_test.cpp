#include "catch.hpp"

/*
Really, compiler will generate same ASM code for & 1 and % 2.
And better to use 1U and 2U to avoid problems with sign.
*/

TEST_CASE("Check bit even/odd code")
{
    REQUIRE((0 & 1) == (0 % 2));
    REQUIRE((1 & 1) == (1 % 2));
    REQUIRE((2 & 1) == (2 % 2));
    REQUIRE((6 & 1) == (6 % 2));
    REQUIRE((7 & 1) == (7 % 2));
}