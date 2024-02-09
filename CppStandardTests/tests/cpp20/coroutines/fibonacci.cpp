#include "../../catch.hpp"

#include <coroutine>
#include <iostream>

#include "templates/variadic.h"

/*
co_await not always will wait/suspend. depending on your decision in bool await_ready();

std::coroutine_handle - raw pointer to coroutine frame
std::coroutine_handle can:
void resume() - resume suspended coroutine
void destroy() - clean up/delete coroutine frame not reached end (when it will be cleaned automatically)
promise_type& promise() const - get promise from coroutine
static coroutine_handle from_promise(promise_type&) - create handler from promise
std::coroutine_handle is not a shared_ptr - plain value!

Caller -> PromiseType
Coroutine -> Awaitable
promise_type <-> coroutine_handler<>

From coroutine:

coroutine has access only to Awaitable and that is the way to pass something out to caller
so in co_await Fibonacci::Awaiter{XXX} we can send XXX to Awaiter to store it
later Awaiter can pass this data to Promise in await_suspend 

from caller we have Fibonacci, from it's c_handle we can get promise and get that value

To coroutine:
Fibonacci -> c_handle -> promise -> resume -> Awaiter -> XXX await_resume() { return promise().XXX; }

instead of returning void in await_suspend you can return another coroutine handler to resume another coroutine instead of returning back to caller
after that you will return to original coroutine
*/

//coroutine handler
struct Fibonacci
{
    struct Promise
    {
        int value;

        //will coroutine suspend when started or will execute
        std::suspend_always initial_suspend() noexcept { Print("initial_suspend"); return {}; }
        //will coroutine suspend when last co_return 
        std::suspend_always final_suspend() noexcept { Print("final_suspend"); return {}; }
        //what to do if there was not an exception that was not catch
        void unhandled_exception() { }
        //function that return my coroutine handler
        Fibonacci get_return_object() noexcept
        {
            Print("get_return_object"); 
            //this needed to get std::coroutine_handle in ReturnType so I can operate with it if needed
            return Fibonacci{ std::coroutine_handle<Promise>::from_promise(*this) };
        };
        //when we reach end of coroutine and no co_return was used
        void return_void() noexcept { }
        //process co_yield value (pass back to caller) and suspend after that
        std::suspend_always yield_value(int v) noexcept
        {
            Print("co_yield", v);
            value = v;
            return {};
        }
        //process co_return  value (pass back to caller) and suspend after that
        //can have either co_return XXX; or no co_return (see return_void)
        //std::suspend_always return_value(int i) noexcept { return {}; }

        //ctor - parameters will be exactly what is send to coroutine function and will be passed here
        Promise()
        {

        }
    };
    using promise_type = Promise;

    //type that I can call co_await on
    struct Awaitable
    {
        //should we continue or suspend executing at co_await... point
        //false means it's never ready, it always want to go to sleep
        //this is like std::suspend_always looks like...
        bool await_ready() noexcept { return false; }
        //will be executed right befor function will goes to suspension
        //can be std::coroutine_handle<> (points on any coroutine) or std::coroutine_handle<promise_type> (exact that type of coroutine)
        //instead of returning void you can return another coroutine handler to resume another coroutine instead of returning back to caller
        void await_suspend(std::coroutine_handle<Promise> h) noexcept 
        {
            Print("co_await", value);
            //store it for later
            c_handle = h;
            //and pass value to promise
            c_handle.promise().value = value;
        }
        //will be called right before coroutine resumed
        //using stored handler we can get some data from promise
        //will not be called if there were no suspend (await_ready return true)
        void await_resume() noexcept {}

        int value;
        std::coroutine_handle<Promise> c_handle;

        Awaitable(int i) :
            value(i)
        {
            
        }
    };

    std::coroutine_handle<Promise> c_handle;

    void resume()
    {
        c_handle.resume();
    }

    int getValue()
    {
        return c_handle.promise().value;
    }
};

Fibonacci FibonacciFunction()
{
    Print("Coroutine started");
    int i1 = 1;
    int i2 = 1;
    bool return_via_yield = false;
    while(true)
    {
        Print("Coroutine about to send data to outta world and pause");
        if (return_via_yield)
            co_yield i1;
        else
            co_await Fibonacci::Awaitable(i1);            
        Print("Coroutine unpaused");
        return_via_yield = !return_via_yield;
        i1 = std::exchange(i2, i1 + i2);
    }
    Print("Coroutine finished");
}

TEST_CASE("Fibonacci")
{
    Fibonacci f_coro = FibonacciFunction();
    //start coroutine
    f_coro.resume();
    //we will get here as soon as coroutine will be paused (in our case by co_yield)
    REQUIRE(f_coro.getValue() == 1);
    //continue coroutine
    f_coro.resume();

    REQUIRE(f_coro.getValue() == 1);
    f_coro.resume();

    REQUIRE(f_coro.getValue() == 2);
    f_coro.resume();

    REQUIRE(f_coro.getValue() == 3);
    f_coro.resume();

    REQUIRE(f_coro.getValue() == 5);
    f_coro.resume();

    REQUIRE(f_coro.getValue() == 8);
    f_coro.resume();

    REQUIRE(f_coro.getValue() == 13);
}