#include <benchmark/benchmark.h>

#include <iostream>
#include <chrono>

#include "TreeGenerator.h"
#include "CompareFunctions.h"

constexpr auto size = 5000000;

static void BM_isSameTreeAGZ(benchmark::State& state)
{
    auto values = GenerateValues(size);
    auto tree1 = GenerateTree(values);
    auto tree2 = GenerateTree(size);
    values[size - 10] -= 1;
    auto tree3 = GenerateTree(values);
    for (auto _ : state)
    {
        isSameTreeAGZ(tree1, tree1);
        isSameTreeAGZ(tree1, tree2);
        isSameTreeAGZ(tree1, tree3);
    }
}
BENCHMARK(BM_isSameTreeAGZ);

static void BM_isSameTreeLeetCode(benchmark::State& state)
{
    auto values = GenerateValues(size);
    auto tree1 = GenerateTree(values);
    auto tree2 = GenerateTree(size);
    values[size - 10] -= 1;
    auto tree3 = GenerateTree(values);
    for (auto _ : state)
    {
        isSameTreeLeetCode(tree1, tree1);
        isSameTreeLeetCode(tree1, tree2);
        isSameTreeLeetCode(tree1, tree3);
    }
}
BENCHMARK(BM_isSameTreeLeetCode);

int main(int argc, char** argv)
{
    char arg0_default[] = "benchmark";
    char* args_default = arg0_default;
    if (!argv)
    {
        argc = 1;
        argv = &args_default;
    }
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv))
        return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();

    {
        auto values = GenerateValues(size);
        auto tree1 = GenerateTree(values);
        auto tree2 = GenerateTree(size);
        values[size - 10] -= 1;
        auto tree3 = GenerateTree(values);
        auto time1 = std::chrono::steady_clock::now();
        isSameTreeAGZ(tree1, tree1);
        isSameTreeAGZ(tree1, tree2);
        isSameTreeAGZ(tree1, tree3);
        auto time2 = std::chrono::steady_clock::now();
        std::cout << "AGZ: " << std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1) << "\n";
    }

    {
        auto values = GenerateValues(size);
        auto tree1 = GenerateTree(values);
        auto tree2 = GenerateTree(size);
        values[size - 10] -= 1;
        auto tree3 = GenerateTree(values);
        auto time1 = std::chrono::steady_clock::now();
        isSameTreeLeetCode(tree1, tree1);
        isSameTreeLeetCode(tree1, tree2);
        isSameTreeLeetCode(tree1, tree3);
        auto time2 = std::chrono::steady_clock::now();
        std::cout << "LeetCode: " << std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1) << "\n";
    }

    return 0;
} 