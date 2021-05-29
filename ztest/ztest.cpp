module ztest;
import std.core;

namespace ztest
{
    struct Case::Impl
    {
        std::vector<std::pair<std::string, bool>> m_case;
    };

    struct Test::Impl
    {
        std::map<std::string, Case> m_case;
        std::string m_current;
        bool checked = false;
    };

    //Test::defaultTester;
    Test Test::defaultTester;

    Case::Case()
        : impl(std::make_shared<Impl>())
    {
    }

    Test::Test()
        : impl(std::make_shared<Impl>())
    {
    }

    Test::~Test()
    {
        if (!impl->checked)
        {
            check();
        }
    }

    void Case::require(std::pair<std::string, bool> _tuple)
    {
        impl->m_case.push_back(_tuple);
    }

    void Test::addCase(std::string _case)
    {
        impl->m_current = _case;
        Case c;
        impl->m_case[_case] = c;
    }

    void Test::require(std::pair<std::string, bool> _tuple)
    {
        impl->m_case[impl->m_current].require(_tuple);
    }

    void Test::check()
    {
        std::map<std::string, Case> passed;
        std::map<std::string, Case> failed;

        for (auto& i : impl->m_case)
        {
            auto result = std::all_of(i.second.impl->m_case.begin(), i.second.impl->m_case.end(),
                [](std::pair<std::string, bool> c) { return c.second; });
            if (result)
            {
                passed[i.first] = i.second;
            }
            else
            {
                failed[i.first] = i.second;
            }
        }

        for (auto& i : passed)
        {
            std::cout << i.first << std::endl;
            std::cout << "  passed" << std::endl;
        }

        for (auto& i : failed)
        {
            std::cout << i.first << std::endl;
            for (auto& j : i.second.impl->m_case)
            {
                if (!j.second)
                {
                    std::cout << "  " << j.first << " failed" << std::endl;
                }
            }
        }

        impl->checked = true;
    }
}
