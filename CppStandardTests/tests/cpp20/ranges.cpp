#include "../catch.hpp"

#include <iostream>
#include <algorithm>
#include <ranges>

TEST_CASE("Simple range example")
{
    std::vector<int> integers = { 1, 2, 3, 4, 5, 6 };

    //idea is to take only odd values and then return a^2
    auto filterFnc = [](const auto& a) { return a % 2 == 1; };
    auto squareFnc = [](const auto& a) { return a * a; };


    decltype(integers) integers2;
    //function way of work
    for (const auto& i : std::views::transform(
        std::views::filter(integers, filterFnc),
        squareFnc))
        integers2.push_back(i);
    REQUIRE(integers2.size() == 3);
    REQUIRE(integers2[0] == 1);
    REQUIRE(integers2[1] == 9);
    REQUIRE(integers2[2] == 25);

    decltype(integers) integers3;
    for(const auto& i : integers | std::views::filter(filterFnc) | std::views::transform(squareFnc))
        integers3.push_back(i);
    REQUIRE(integers3.size() == 3);
    REQUIRE(integers3[0] == 1);
    REQUIRE(integers3[1] == 9);
    REQUIRE(integers3[2] == 25);
}