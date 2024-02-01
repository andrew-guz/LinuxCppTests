#pragma once

#include "test_helper.h"

#include <thread>

namespace ThreadsTest
{
    void Worker1(int count)
    {
        for (auto i = 0; i < count; ++i)
        {
            Print(i);
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    }
};

class Threads : public TestBase
{
public:
    virtual const char* Name() const override
    {
        return "threads";
    }

protected:
    virtual void TestImpl() override
    {
        Print("starting thread");
        std::thread t1(ThreadsTest::Worker1, 5);
        t1.join();
        Print("thread joined");

        Print("starting thread");
        std::thread t2(ThreadsTest::Worker1, 5);
        t2.detach();
        Print("thread detached");

        //wait for t2 to be finished cause it will harm output of next Tests
        std::this_thread::sleep_for(1s);
    }
};
