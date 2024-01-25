#pragma once

#include <iostream>
#include <vector>
#include <memory>

class TestBase
{
public:
    TestBase() = default;

    virtual ~TestBase() = default;

    virtual const char* Name() const = 0;

    void Test()
    {
        std::cout << "---" << Name() << "---" << std::endl;
        TestImpl();
        std::cout << "------" << std::endl;
    }

protected:
    virtual void TestImpl() = 0;
};

class Tests final
{
protected:
    Tests() = default;

public:
    static Tests& instance()
    {
        static Tests s_instance;
        return s_instance;
    }

    template<typename T>
    void RegisterTest()
    {
        _tests.push_back(std::make_shared<T>());
    }

    void Run()
    {
        for(auto& test : _tests)
            test->Test();
    }

private:
    std::vector<std::shared_ptr<TestBase>> _tests;
};

#define REGISTER_TEST(x) Tests::instance().RegisterTest<x>()
