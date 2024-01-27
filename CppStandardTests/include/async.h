#pragma once

#include "test_helper.h"

#include <future>
#include <thread>
#include <chrono>
#include <functional>

using namespace std::literals::chrono_literals;

namespace AsyncTest
{
    void WorkerFunction()
    {
        for (auto i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(100ms);
            PRINT(i);
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
                PRINT("A::WorkerFunction_" << count << " " << i);
            }
        }
    };
};

class Async : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "async";
    }

protected:
    virtual void TestImpl() override
    {
        auto futureAsync = std::async(std::launch::async, AsyncTest::WorkerFunction);
        PRINT("Waiting async");
        futureAsync.wait();
        PRINT("Done async");

        auto futureDeferred = std::async(std::launch::deferred, AsyncTest::WorkerFunction);
        PRINT("Waiting deffered");
        PRINT("Done deffered");
        //since std::launch::deferred will not be calculated till future.wait

        std::async(std::launch::async, []{
            for (auto i = 0; i < 10; ++i)
            {
                std::this_thread::sleep_for(100ms);
                PRINT("lambda " << i);
            }
        }).wait();
        

        AsyncTest::A a1;
        std::async(std::launch::async, std::bind(&AsyncTest::A::WorkerFunction, a1, std::placeholders::_1), 5).wait();
    }
};
