#include "../../catch.hpp"

#include <coroutine>

//from corutine using yield
struct YieldReturn
{
    struct Promise
    {
        int _value;

        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        YieldReturn get_return_object() { return YieldReturn{ std::coroutine_handle<Promise>::from_promise(*this) }; }
        std::suspend_always yield_value(int v)
        {
            _value = v;
            return {};
        }
    };
    using promise_type = Promise;

    std::coroutine_handle<Promise> _co_handle;

    void resume()
    {
        _co_handle.resume();
    }

    int value()
    {
        return _co_handle.promise()._value;
    }
};

YieldReturn TestYieldReturn()
{
    co_yield 5;
}

TEST_CASE("Yield return")
{
    YieldReturn yield_return = TestYieldReturn();
    yield_return.resume();
    REQUIRE(yield_return.value() == 5);
}

/***************************************************/

//from corutine using return
struct CoReturn
{
    struct Promise
    {
        int _value;

        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        CoReturn get_return_object() { return CoReturn{ std::coroutine_handle<Promise>::from_promise(*this) }; }
        std::suspend_always return_value(int v)
        {
            _value = v;
            return {};
        }
    };
    using promise_type = Promise;

    std::coroutine_handle<Promise> _co_handle;

    void resume()
    {
        _co_handle.resume();
    }

    int value()
    {
        return _co_handle.promise()._value;
    }
};

CoReturn TestCoReturn()
{
    co_return 7;
}

TEST_CASE("Coroutine return")
{
    CoReturn coroutine_return = TestCoReturn();
    coroutine_return.resume();
    REQUIRE(coroutine_return.value() == 7);
}

/***************************************************/

//from coroutine using await and ctor
struct AwaitReturn1
{
    struct Promise
    {
        int _value;

        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        AwaitReturn1 get_return_object() { return AwaitReturn1{ std::coroutine_handle<Promise>::from_promise(*this) }; }
    };
    using promise_type = Promise;

    struct Awaiter
    {
        int _value;

        bool await_ready() noexcept { return false; }
        void await_suspend(std::coroutine_handle<Promise> h) noexcept 
        {
            h.promise()._value = _value;
        }
        void await_resume() noexcept {}
    };

    std::coroutine_handle<Promise> _co_handle;

    void resume()
    {
        _co_handle.resume();
    }

    int value()
    {
        return _co_handle.promise()._value;
    }
};

AwaitReturn1 TestAwaitReturn1()
{
    co_await AwaitReturn1::Awaiter{9};
}

TEST_CASE("Await return 1")
{
    AwaitReturn1 await_return_1 = TestAwaitReturn1();
    await_return_1.resume();
    REQUIRE(await_return_1.value() == 9);
}

/***************************************************/

//from coroutine using await and await_transform
//pay attention that await_transform is a promise_type function
struct AwaitReturn2
{
    struct Promise
    {
        int _value;

        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        AwaitReturn2 get_return_object() { return AwaitReturn2{ std::coroutine_handle<Promise>::from_promise(*this) }; }

        auto await_transform(int v)
        {
            struct Awaiter
            {
                int _value;

                bool await_ready() noexcept { return false; }
                void await_suspend(std::coroutine_handle<Promise> h) noexcept 
                {
                    h.promise()._value = _value;
                }
                void await_resume() noexcept {}
            };

            return Awaiter{v};
        }
    };
    using promise_type = Promise;

    std::coroutine_handle<Promise> _co_handle;

    void resume()
    {
        _co_handle.resume();
    }

    int value()
    {
        return _co_handle.promise()._value;
    }
};

AwaitReturn2 TestAwaitReturn2()
{
    co_await 13;
}

TEST_CASE("Await return 2")
{
    AwaitReturn2 await_return_2 = TestAwaitReturn2();
    await_return_2.resume();
    REQUIRE(await_return_2.value() == 13);
}

/***************************************************/

//to coroutine using awiat and from corutine using yield
struct ToCoroutineAndBackReturn
{
    struct Promise
    {
        int _value;

        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        ToCoroutineAndBackReturn get_return_object() { return ToCoroutineAndBackReturn{ std::coroutine_handle<Promise>::from_promise(*this) }; }
        std::suspend_always yield_value(int v)
        {
            _value = v;
            return {};
        }
    };
    using promise_type = Promise;

    struct Awaiter
    {
        std::coroutine_handle<Promise> _co_handle;

        bool await_ready() noexcept { return false; }
        void await_suspend(std::coroutine_handle<Promise> h) noexcept
        {
            _co_handle = h;
        }
        int await_resume() noexcept
        {
            return _co_handle.promise()._value;
        }
    };

    std::coroutine_handle<Promise> _co_handle;

    void resume()
    {
        _co_handle.resume();
    }

    void setValue(int v)
    {
        _co_handle.promise()._value = v;
    }

    int value()
    {
        return _co_handle.promise()._value;
    }
};

ToCoroutineAndBackReturn TestToCoroutineAndBackReturn()
{
    int a = co_await ToCoroutineAndBackReturn::Awaiter{};
    co_yield (a * 2);
}

TEST_CASE("To coroutine using await and back")
{
    ToCoroutineAndBackReturn to_and_back = TestToCoroutineAndBackReturn();
    to_and_back.resume();
    to_and_back.setValue(15);
    to_and_back.resume();
    REQUIRE(to_and_back.value() == 30);
}
