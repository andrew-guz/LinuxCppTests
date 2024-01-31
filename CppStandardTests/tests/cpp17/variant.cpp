#include "../catch.hpp"

#include <variant>

using namespace std::string_literals;

TEST_CASE("Get")
{
    std::variant<int, bool, std::string> v = { 5 };
    REQUIRE(std::get<int>(v) == 5);
    REQUIRE(std::get<0>(v) == 5);
    REQUIRE_THROWS(std::get<bool>(v));
    REQUIRE(std::get_if<int>(&v) != nullptr);
    REQUIRE(std::get_if<bool>(&v) == nullptr);    
    v = "Test string"s;
    REQUIRE(std::get<std::string>(v).size() == 11);
    REQUIRE(std::get<2>(v).size() == 11);
}

TEST_CASE("Set not supported type")
{
    std::variant<bool, int> v;
    v = 5;
    v = true;
    //v = 5.6; //COMPILATION ERROR
}

auto visitFunction = [](auto& a)->std::string
{
    using T = std::decay_t<decltype(a)>;
    if constexpr(std::is_same_v<T, bool>)
        return "bool";
    else if constexpr(std::is_same_v<T, int>)
        return "int";
    else
        return "unknown";
};

TEST_CASE("Visit")
{
    std::variant<bool, int> v;
    //pay attention - by default variant initialized as first type
    REQUIRE(std::visit(visitFunction, v) == "bool");
    REQUIRE_FALSE(std::get<bool>(v));
    v = 45;
    REQUIRE(std::visit(visitFunction, v) == "int");
    v = true;
    REQUIRE(std::visit(visitFunction, v) == "bool");
}