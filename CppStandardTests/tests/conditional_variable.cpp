#include "catch.hpp"

#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <execution>
#include <algorithm>
#include <latch>

using namespace std::chrono_literals;

#include "templates/folding.h"

void WorkerThread1(std::latch& started, std::mutex& m, std::condition_variable& c, const std::string& name)
{
    PrintWithSpaces(name, ": started");
    std::unique_lock ul(m);
    PrintWithSpaces(name, ": mutex locked, will wait for notification");
    started.count_down();
    c.wait(ul);
    std::this_thread::sleep_for(20ms);
    PrintWithSpaces(name, ": finished");
}

TEST_CASE("Notify and start one thread")
{
    std::latch l(1);
    std::mutex m;
    std::condition_variable c;
    std::jthread t(WorkerThread1, std::ref(l), std::ref(m), std::ref(c), "1");
    l.wait();
    PrintWithSpaces("Send notification");
    c.notify_one();
}

TEST_CASE("Notify and start several threads thread")
{
    constexpr int threads_count = 5;
    std::latch l(threads_count);
    std::mutex m;
    std::condition_variable c;
    std::vector<std::jthread> threads{threads_count};
    for (int i = 0; i < threads_count; ++i)
        threads.emplace_back(WorkerThread1, std::ref(l), std::ref(m), std::ref(c), std::to_string(i + 1));
    l.wait();
    PrintWithSpaces("Send notification");
    c.notify_all();
}

struct Context
{
    int data;
    std::mutex mutex;
    std::condition_variable wait_for_result;
    std::condition_variable result_ready;
    bool finish;
};

void WorkerThread2(std::latch& thread_started, Context& context)
{
    std::unique_lock ul{context.mutex};
    thread_started.count_down();
    while(true)
    {
        context.wait_for_result.wait(ul);
        if (context.finish)
            break;
        context.data *= context.data;
        context.result_ready.notify_one();
    }
}

TEST_CASE("Several thread communications")
{
    std::latch l{1};
    Context c{5};
    std::jthread t(WorkerThread2, std::ref(l), std::ref(c));
    l.wait();

    std::unique_lock ul{c.mutex};

    {
        c.data = 5;
        c.wait_for_result.notify_one();
        c.result_ready.wait(ul);
        REQUIRE(c.data == 25);
    }

    {
        c.data = 6;
        c.wait_for_result.notify_one();
        c.result_ready.wait(ul);
        REQUIRE(c.data == 36);
    }

    {
        c.data = 7;
        c.wait_for_result.notify_one();
        c.result_ready.wait(ul);
        REQUIRE(c.data == 49);
    }
    
    c.finish = true;
    c.wait_for_result.notify_one();
}
