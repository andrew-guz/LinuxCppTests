#include "../catch.hpp"

#include <algorithm>
#include <execution>
#include <vector>

struct A
{
    int _i;

    A& operator=(int i)
    {
        _i = i;
        return *this;
    }
};

std::vector<A> CreateVector(size_t count)
{
    std::vector<A> v (count);
    std::iota(v.begin(), v.end(), 1);
    return v;
}

void UpdateElement(A& a)
{
    a._i += 2;
}

TEST_CASE("Sequential")
{
    auto v = CreateVector(5);
    std::for_each(v.begin(), v.end(), UpdateElement);
    for (auto i = 0; i < 5; ++i)
        REQUIRE(v[i]._i == i + 3);
}

TEST_CASE("Parallel")
{
    auto v = CreateVector(1000);
    std::for_each(std::execution::par, v.begin(), v.end(), UpdateElement);
    for (auto i = 0; i < 5; ++i)
        REQUIRE(v[i]._i == i + 3);
}
