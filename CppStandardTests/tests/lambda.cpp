#include "catch.hpp"

#include "templates/variadic.h"

/*
Lambda will be generated as a struct with inline operator() (callable)
This operator() will be CONST

You can mark lambda as mutable (otherwise generator operator will be const) or noexcept
Example: [](){} mutable noexcept

Lambda with no capture will be passed to function as a function pointer. 
Example [](int)-> int{} -> (int*f)(int)

Lambda can capture only local variables.
Global variables or static variable, event which is nearby, will not be captured.
They will be just "accessed".

Even in in text two lambdas are "equal", different closure types will be generated.
*/

TEST_CASE("Static capture")
{
    int i = 0;
    static int j = 0;
    //marked as mutable or can't ++i captured by value
    auto f = [=]() mutable
    {
        ++i;
        ++j;
    };
    f();
    REQUIRE(i == 0); //i captured by value [=] and was not modified
    REQUIRE(j == 1); //j was not captured as static and was just modified
}

/*
This is THREAD safe
Also there is a std::call_once doing the same
*/
TEST_CASE("Single function")
{
    static int i = 0;

    struct X
    {
        X()
        {
            [[maybe_unused ]]static auto _ = []()
            {
                i += 1;
                return 0;
            }();
        }
    };

    X x1;
    X x2;
    X x3;
    REQUIRE(i == 1);
}

TEST_CASE("Types")
{
    auto f1 = [](){};
    auto f2 = [](){};
    REQUIRE_FALSE(std::is_same_v<decltype(f1), decltype(f2)>);
    auto f3 = f1;
    REQUIRE(std::is_same_v<decltype(f1), decltype(f3)>);
}
