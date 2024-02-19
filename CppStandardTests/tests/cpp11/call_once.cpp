#include "../catch.hpp"

#include <mutex>

int i = 0;
std::once_flag flag;

struct X
{
    X()
    {
        std::call_once(flag, [](){
            ++i;
        });
    }
};

TEST_CASE("Call once example")
{
    REQUIRE(i == 0);
    X x1;
    X x2;
    X x3;
    REQUIRE(i == 1);
}