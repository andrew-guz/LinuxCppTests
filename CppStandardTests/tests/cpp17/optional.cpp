#include "../catch.hpp"

#include <optional>
#include <vector>

struct A
{
    int _id;
    int _i;
    bool _j;
};

std::optional<A> FindById(const std::vector<A>& container, int id)
{
    auto iter = std::find_if(container.begin(), container.end(), [id](const auto& a){ return a._id == id; });
    if (iter != container.end())
        return std::make_optional(*iter);
    return {};
}

TEST_CASE()
{
    std::vector<A> v;
    v.emplace_back(1, 2, true);
    v.emplace_back(4, 5, false);
    auto value = FindById(v, 1);
    REQUIRE(value.has_value());
    REQUIRE(value->_i == 2);
    REQUIRE(value->_j);
    REQUIRE(FindById(v, 4).has_value());
    REQUIRE_FALSE(FindById(v, 2).has_value());
}