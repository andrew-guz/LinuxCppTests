#pragma once

#include "test_helper.h"

#include <thread>

namespace ThreadsTest
{
    void Worker1(int count)
    {
        for (auto i = 0; i < count; ++i)
        {
            PRINT(i);
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    }
};

class Threads : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "threads";
    }

protected:
    virtual void TestImpl() override
    {
        PRINT("starting thread");
        std::thread t1(ThreadsTest::Worker1, 5);
        t1.join();
        PRINT("thread joined");

        PRINT("starting thread");
        std::thread t2(ThreadsTest::Worker1, 5);
        t2.detach();
        PRINT("thread detached");
    }
};
