export module ztest;
import std.core;

export
{
    namespace ztest
    {
        class Case
        {
        public:
            Case();
            ~Case() = default;

            void require(std::pair<std::string, bool> _tuple);

            friend class Test;

        private:
            struct Impl;
            std::shared_ptr<Impl> impl;
        };

        class Test
        {
        public:
            Test();
            ~Test();

            void addCase(std::string _case);

            void require(std::pair<std::string, bool> _tuple);

            void check();

            static Test defaultTester;


        private:
            struct Impl;
            std::shared_ptr<Impl> impl;
        };

        Test& get();
    }
}
