#include "../../catch.hpp"

#include <iostream>
#include <string>
#include <coroutine>

using namespace std::string_literals;

struct StringGenerator
{
    struct promise_type
    {
        std::string incoming_message;
        std::string outgoing_message;

        void unhandled_exception() {}
        StringGenerator get_return_object() { return StringGenerator(this); }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(const std::string msg) noexcept
        {
            outgoing_message = std::move(msg);
            return {};
        }
        void return_value(std::string msg) noexcept
        {
            outgoing_message = std::move(msg);
        }
    };

    std::coroutine_handle<promise_type> coroutine_handler;

    explicit StringGenerator(promise_type* p) :
        coroutine_handler(std::coroutine_handle<promise_type>::from_promise(*p))
    {
        
    }

    StringGenerator(StringGenerator&& other) :
        coroutine_handler(std::exchange(other.coroutine_handler, nullptr))
    {
        
    }

    ~StringGenerator()
    {
        if (coroutine_handler)
            coroutine_handler.destroy();
    }

    bool isDone() const noexcept
    {
        return coroutine_handler.done();
    }

    std::string getNextString()
    {
        if (!coroutine_handler.done())
            coroutine_handler.resume();
        return std::move(coroutine_handler.promise().outgoing_message);
    }
};

StringGenerator GenerateStrings()
{
    co_yield "test string 1"s;
    co_yield "test string 2"s;
    co_return "test string 3"s;
}

TEST_CASE("Coroutine example 1")
{
    StringGenerator coroutine1 = GenerateStrings();

    REQUIRE(coroutine1.getNextString() == "test string 1"s);
    REQUIRE(coroutine1.getNextString() == "test string 2"s);
    REQUIRE(coroutine1.getNextString() == "test string 3"s);

    StringGenerator coroutine2 = GenerateStrings();
    while(!coroutine2.isDone())
        std::cout << coroutine2.getNextString() << std::endl;
}
