#include "../catch.hpp"

#include <variant>
#include <numbers>
#include <vector>

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

enum class ShapeType
{
    Circle,
    Square
};

struct Shape
{
    virtual ShapeType type() const = 0;

    virtual double perimeter() const = 0;
};

struct Circle : public Shape
{
    double _radius;

    Circle(double r) :
        _radius(r)
    {

    }

    virtual ShapeType type() const override { return ShapeType::Circle; }

    virtual double perimeter() const override { return 2.0 * std::numbers::pi * _radius; }
};

struct Square : public Shape
{
    double _side;

    Square(double s) :
        _side(s)
    {

    }

    virtual ShapeType type() const override { return ShapeType::Square; }

    virtual double perimeter() const override { return 4.0 * _side; }
};

TEST_CASE("Variant for polymorphism")
{
    std::vector<std::variant<Circle, Square>> figures;
    figures.emplace_back(Circle(5));
    figures.emplace_back(Square(5));
    for (const auto& figure : figures)
        std::visit([](const auto& f)
        {
            auto p = f.perimeter();
            double expected_p = 0.0;
            switch(f.type())
            {
                case ShapeType::Circle:
                    expected_p = 2.0 * std::numbers::pi * 5.0;
                    break;
                case ShapeType::Square:
                    expected_p = 4.0 * 5.0;
                    break;
            }
            REQUIRE(p == expected_p);
        }, figure);
}
