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
    started.count_down();
    PrintWithSpaces(name, ": started");
    std::unique_lock ul(m);
    PrintWithSpaces(name, ": mutex locked, will wait for notification");
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