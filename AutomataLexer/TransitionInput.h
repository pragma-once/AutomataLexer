#pragma once

#include <string>

namespace AutomataLexer
{
    class TransitionInput
    {
        public:

        TransitionInput(const std::string&);
        TransitionInput(char);
        TransitionInput(char Min, char Max);
        ~TransitionInput();
        TransitionInput(const TransitionInput&) noexcept;
        TransitionInput(TransitionInput&&) noexcept;
        TransitionInput& operator=(TransitionInput) noexcept;
        /// @brief Reads the string from the given index and returns the new index if satisfied,
        ///        else returns the given index.
        int Read(const std::string&, int);

        private:

        class Data
        {
            public:
            virtual ~Data() = default;
            virtual Data * Clone() = 0;
            virtual int Read(const std::string&, int) = 0;
        };
        class StringData : public Data
        {
            public:
            StringData(const std::string&);
            virtual Data * Clone() override;
            virtual int Read(const std::string&, int) override;
            private:
            std::string Expectation;
        };
        class CharRangeData : public Data
        {
            public:
            CharRangeData(char Min, char Max);
            virtual Data * Clone() override;
            virtual int Read(const std::string&, int) override;
            private:
            char Min, Max;
        };
        class CharData : public Data
        {
            public:
            CharData(char);
            virtual Data * Clone() override;
            virtual int Read(const std::string&, int) override;
            private:
            char Expectation;
        };

        Data * DataPtr;
    };
}
