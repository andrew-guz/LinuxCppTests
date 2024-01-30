#pragma once

#include "test_helper.h"

#include <optional>
#include <algorithm>

namespace UseOptionalTest
{
    struct A
    {
        int _id;
        int _i;
        bool _j;
    };

    std::optional<A> FindById(const std::vector<A>& container, int id)
    {
        auto iter = std::find_if(container.begin(), container.end(), [id](const auto& a){ return a._id == id; });
        if (iter != container.end())
            return std::make_optional(*iter);
        return {};
    }
};

class UseOptional : public TestBase
{
public:
    virtual const char* Name() const
    {
        return "optional";
    }

protected:
    void TestOptional(const std::optional<UseOptionalTest::A>& a)
    {
        if (a.has_value())
            Print(a.value()._i, a.value()._j);
        else
            Print("Not found");
    }

    virtual void TestImpl() override
    {
        std::vector<UseOptionalTest::A> v;
        v.emplace_back(1, 2, 3);
        v.emplace_back(4, 5, 6);
        TestOptional(UseOptionalTest::FindById(v, 1));
        TestOptional(UseOptionalTest::FindById(v, 2));
    }
};
