#include "../../catch.hpp"

#include <coroutine>
#include <vector>

using namespace std::string_literals;

struct Multiplier
{
    struct Promise
    {
        int member;
        int multiplication;

        void unhandled_exception() {}
        Multiplier get_return_object() { return Multiplier{ std::coroutine_handle<Promise>::from_promise(*this)}; }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(const int m) noexcept { multiplication = m; return {}; }
    };
    using promise_type = Promise;

    struct Awaiter
    {
        std::coroutine_handle<Promise> c_handle;

        constexpr bool await_ready() const noexcept { return false; }
        constexpr void await_suspend(std::coroutine_handle<Promise> h) noexcept
        { 
            c_handle = h;
        }
        int await_resume() const noexcept
        {
            return c_handle.promise().member;
        }
    };

    std::coroutine_handle<Promise> c_handle;

    bool isDone() const noexcept
    {
        return c_handle.done();
    }

    void resume()
    {
        c_handle.resume();
    }

    void sendMultiplier(int val)
    {
        c_handle.promise().member = val;
    }

    int getResult()
    {
        return c_handle.promise().multiplication;
    }
};

Multiplier Multiply()
{
    while(true)
    {
        int a = co_await Multiplier::Awaiter();
        int b = co_await Multiplier::Awaiter();
        co_yield (a*b);
    }
}

int DoTheMultiply(Multiplier& multiplier, int a, int b)
{
    multiplier.resume();
    multiplier.sendMultiplier(a);
    multiplier.resume();
    multiplier.sendMultiplier(b);
    multiplier.resume();
    return multiplier.getResult();
}

TEST_CASE("Multiplier example")
{
    Multiplier multiplier = Multiply();
    REQUIRE(DoTheMultiply(multiplier, 2, 3) == 6);
    REQUIRE(DoTheMultiply(multiplier, 7, 4) == 28);
    REQUIRE(DoTheMultiply(multiplier, 1, 99) == 99);
}
