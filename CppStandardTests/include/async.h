#pragma once

#include "test_helper.h"

#include <future>
#include <thread>
#include <chrono>
#include <functional>

/*
Interesting moment. If future is not saved anywhere from async,
in it's dtor it will wait for async to be finished.
*/

using namespace std::literals::chrono_literals;

namespace AsyncTest
{
    void WorkerFunction()
    {
        for (auto i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(100ms);
            Print(i);
        }
    }

    class A
    {
    public:
        void WorkerFunction(uint count)
        {
            for (auto i = 0u; i < count; ++i)
            {
                std::this_thread::sleep_for(100ms);
                Print("A::WorkerFunction_" + std::to_string(count), i);
            }
        }
    };
};

class Async : public TestBase
{
public:
    virtual const char* Name() const override
    {
        return "async";
    }

protected:
    virtual void TestImpl() override
    {
        auto futureAsync = std::async(std::launch::async, AsyncTest::WorkerFunction);
        Print("Waiting async");
        futureAsync.wait();
        Print("Done async");

        auto futureDeferred = std::async(std::launch::deferred, AsyncTest::WorkerFunction);
        Print("Waiting deffered");
        Print("Done deffered");
        //since std::launch::deferred will not be calculated till future.wait

        std::async(std::launch::async, []{
            for (auto i = 0; i < 10; ++i)
            {
                std::this_thread::sleep_for(100ms);
                Print("lambda " + std::to_string(i));
            }
        }).wait();
        

        AsyncTest::A a1;
        std::async(std::launch::async, std::bind(&AsyncTest::A::WorkerFunction, a1, std::placeholders::_1), 5).wait();
    }
};
