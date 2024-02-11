#include "../catch.hpp"

#include <thread>
#include <stop_token>
#include <chrono>

#include "templates/folding.h"

void func1(std::string name)
{
    for (auto i = 0; i < 10; ++i)
    {
        PrintWithSpaces(name, i + 1, "...");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

//even if jt1 goes ou of scope, thread will be finished, because dtor will join
TEST_CASE("Simple jthread")
{
    std::jthread jt1{ func1, "jt1" };
    {
        std::jthread jt2{ func1, "jt2" };
    }
}

void func2(std::stop_token st, std::string name)
{
    for (auto i = 0; i < 10; ++i)
    {
        PrintWithSpaces(name, i + 1, "...");
        if (st.stop_requested())
        {
            PrintWithSpaces("Cancelled");
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

TEST_CASE("Cancellation")
{
    {
        //at dtor
        std::jthread jt3{ func2, "jt3" };
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    {
        //by hands
        std::stop_source ss;
        std::jthread jt4{ func2, ss.get_token(), "jt4" };
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ss.request_stop();
    }
    {
        //by hands not passing stop source
        std::jthread jt4{ func2, "jt4" };
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        jt4.get_stop_source().request_stop();
    }
}

void func3(std::stop_token st, std::string name)
{
    std::stop_callback sc(st, []()
    {
        PrintWithSpaces("Cancelled");
    });
    for (auto i = 0; i < 10; ++i)
    {
        PrintWithSpaces(name, i + 1, "...");
        if (st.stop_requested())
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

TEST_CASE("Cancellation callback")
{
    std::jthread jt5{ func3, "jt5" };
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}