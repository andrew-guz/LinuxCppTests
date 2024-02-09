#include "../catch.hpp"

#include <future>
#include <memory>
#include <thread>
#include <chrono>

#include "templates/variadic.h"

void ThreadFuture(std::shared_ptr<std::promise<int>> promise)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    promise->set_value(10);
}

TEST_CASE("Promise future pair")
{
    auto promise = std::make_shared<std::promise<int>>();
    auto future = promise->get_future();
    std::thread thread(ThreadFuture, promise);
    thread.detach();
    while (future.wait_for(std::chrono::milliseconds(50)) != std::future_status::ready)
        Print("Waiting for thread to be finished...");
    Print("Finished");
    REQUIRE(future.get() == 10);
}
