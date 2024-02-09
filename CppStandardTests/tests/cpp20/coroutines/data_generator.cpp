#include "../../catch.hpp"

#include <iostream>
#include <string>
#include <coroutine>
#include <variant>

using namespace std::string_literals;

struct DataGenerator
{
    struct promise_type
    {
        std::variant<std::string, int> data;

        void unhandled_exception() {}
        DataGenerator get_return_object() { return DataGenerator(this); }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(const std::string msg) noexcept
        {
            data = std::move(msg);
            return {};
        }
        std::suspend_always yield_value(const int i) noexcept
        {
            data = i;
            return {};
        }
        void return_value(const std::string msg) noexcept
        {
            data = std::move(msg);
        }
        void return_value(const int i) noexcept
        {
            data = i;
        }
    };

    std::coroutine_handle<promise_type> coroutine_handler;

    explicit DataGenerator(promise_type* p) :
        coroutine_handler(std::coroutine_handle<promise_type>::from_promise(*p))
    {
        
    }

    DataGenerator(DataGenerator&& other) :
        coroutine_handler(std::exchange(other.coroutine_handler, nullptr))
    {
        
    }

    ~DataGenerator()
    {
        if (coroutine_handler)
            coroutine_handler.destroy();
    }

    bool isDone() const noexcept
    {
        return coroutine_handler.done();
    }

    std::variant<std::string, int> getNextData()
    {
        if (!coroutine_handler.done())
            coroutine_handler.resume();
        return std::move(coroutine_handler.promise().data);
    }
};

DataGenerator GenerateData()
{
    co_yield "test string 1"s;
    co_yield 4;
    co_yield "test string 2"s;
    co_yield 5;
    co_return "test string 3"s;
}

void print(const std::variant<std::string, int>& var)
{
    if (std::holds_alternative<std::string>(var))
        std::cout << std::get<std::string>(var) << std::endl;
    else if (std::holds_alternative<int>(var))
        std::cout << std::get<int>(var) << std::endl;
}

TEST_CASE("Data generator example")
{
    DataGenerator coroutine1 = GenerateData();
    while(!coroutine1.isDone())
        print(coroutine1.getNextData());

    DataGenerator coroutine2 = GenerateData();
    REQUIRE(std::get<std::string>(coroutine2.getNextData()) == "test string 1"s);
    REQUIRE(std::get<int>(coroutine2.getNextData()) == 4);
    REQUIRE(std::get<std::string>(coroutine2.getNextData()) == "test string 2"s);
    REQUIRE(std::get<int>(coroutine2.getNextData()) == 5);
    REQUIRE(std::get<std::string>(coroutine2.getNextData()) == "test string 3"s);
}
