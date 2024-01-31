#include "../catch.hpp"

#include <any>
#include <string>

using namespace std::string_literals;

class A
{
private:
    std::string _value;
};

TEST_CASE("Has value")
{
    std::any a;
    REQUIRE_FALSE(a.has_value());
    a = 5;
    REQUIRE(a.has_value());
    auto i = std::any_cast<int>(a);
    REQUIRE(i == 5);
    a.reset();
    REQUIRE_FALSE(a.has_value());
    a = A {};
    REQUIRE(a.has_value());
}

template<typename T>
T convert(const std::any& a, bool should_be_converted)
{
    try
    {
        auto value = std::any_cast<T>(a);
        REQUIRE(should_be_converted);
        return value;
    }
    catch(...)
    {
        REQUIRE_FALSE(should_be_converted);
        return {};
    }
}

TEST_CASE("Conversion")
{
    std::any a = 5;    
    convert<std::string>(a, false);
    convert<float>(a, false);
    a = "Hello";
    convert<std::string>(a, false);
    convert<const char*>(a, true);
}
