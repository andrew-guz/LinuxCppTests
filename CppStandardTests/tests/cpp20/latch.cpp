#include "../catch.hpp"

#include "templates/folding.h"

#include <thread>
#include <latch>
#include <random>
#include <chrono>

using namespace std::string_literals;

void func(std::string name, std::latch& start_latch, std::latch& finish_latch)
{
    start_latch.arrive_and_wait();
    PrintWithSpaces("Thread", name, "started");
    std::random_device rd;
    std::default_random_engine dre(rd());
    std::uniform_int_distribution<int> uniform_dist(50, 150);
    std::this_thread::sleep_for(std::chrono::milliseconds(uniform_dist(dre)));
    PrintWithSpaces("Thread", name, "finished");
    finish_latch.count_down();
}

TEST_CASE("Latch usage example")
{
    const auto threads_count = 5;
    std::vector<std::jthread> threads;
    std::latch start_latch{threads_count};
    std::latch finish_latch{threads_count};
    for (auto i = 0; i < 5; ++i)
        threads.push_back(std::jthread{ func, "jt"s + std::to_string(i + 1), std::ref(start_latch), std::ref(finish_latch) });
    finish_latch.wait();
    PrintWithSpaces("All threads finished");
}