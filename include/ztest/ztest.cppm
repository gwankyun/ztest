module;
#include "module.h"
#include <Windows.h>
export module ztest;
import std.core;

EXPORT_BEGIN
namespace ztest
{
#ifndef ZTEST_COLOR
#  if defined(_WIN32) && !defined(WINCE)
#    define ZTEST_COLOR 1
#  else
#    define ZTEST_COLOR 0
#  endif
#endif

#if ZTEST_COLOR
    struct ConsoleTextAttribute
    {
        ConsoleTextAttribute(HANDLE handle, WORD attribute)
            : m_handle(handle)
        {
            SetConsoleTextAttribute(handle, attribute);
        }
        ~ConsoleTextAttribute()
        {
            SetConsoleTextAttribute(m_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        HANDLE m_handle;
    };
#endif

    class Case
    {
    public:
        Case()
            : impl(std::make_shared<Impl>())
        {
        }

        ~Case() = default;

        void require(const std::pair<std::string, bool>& _tuple)
        {
            impl->m_case.push_back(_tuple);
        }

        bool check(bool _show = true)
        {
            bool ret = true;
            for (auto& i : impl->m_case)
            {
                if (!i.second)
                {
                    ret = false;
                    if (_show)
                    {
                        {
                            ConsoleTextAttribute textAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                            std::cout << "  failed ";
                        }
                        std::cout << i.first << std::endl;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            return ret;
        }

        friend class Test;

    private:
        struct Impl
        {
            std::vector<std::pair<std::string, bool>> m_case;
        };

        std::shared_ptr<Impl> impl;
    };

    class Test
    {
    public:
        Test()
            : impl(std::make_unique<Impl>())
        {
        }

        ~Test()
        {
            if (!impl->m_checked)
            {
                check();
            }
        }

        void addCase(const std::string& _case)
        {
            impl->m_current = _case;
            Case c;
            impl->m_case[_case] = c;
        }

        void require(const std::pair<std::string, bool>& _tuple)
        {
            impl->m_case[impl->m_current].require(_tuple);
        }

        void check()
        {
            for (auto& i : impl->m_case)
            {
                std::cout << i.first << std::endl;
                auto result = i.second.check(false);
                if (result)
                {
                    ConsoleTextAttribute textAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    std::cout << "  passed" << std::endl;
                }
                else
                {
                    i.second.check();
                }
            }
            impl->m_checked = true;
        }

    private:
        struct Impl
        {
            std::map<std::string, Case> m_case;
            std::string m_current;
            bool m_checked = false;
        };

        std::unique_ptr<Impl> impl;
    };

    inline Test& get()
    {
        static Test defaultTester;
        return defaultTester;
    }

    void testCase(const char* _case)
    {
        get().addCase(_case);
    }
}
EXPORT_END
