#pragma once

#include "templates/variadic.h"

#include <vector>
#include <memory>
#include <cstring>

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
        _tests.emplace_back(new T());
    }

    void RunAll()
    {
        for(auto& test : _tests)
            test->Test();
    }

    void RunExact(const char* name)
    {
        for(auto& test : _tests)
            if (strcmp(test->Name(), name) == 0)
                test->Test();
    }

private:
    std::vector<std::shared_ptr<TestBase>> _tests;
};

#define REGISTER_TEST(x) Tests::instance().RegisterTest<x>()
