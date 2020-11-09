#pragma once

#include <initializer_list>
#include <map>
#include <vector>

#include "TransitionInput.h"

namespace AutomataLexer
{
    class StateMachine
    {
        public:

        StateMachine();
        void AddTransition(std::string FromState, std::initializer_list<TransitionInput> InputSet, std::string ToState);
        void AddTransition(std::string FromState, std::vector<TransitionInput> InputSet, std::string ToState);
        // TODO

        private:

        std::map<std::string, std::vector<std::tuple<TransitionInput, std::string>>> States;
        std::string * CurrentStateNamePtr;
        std::vector<std::tuple<TransitionInput, std::string>> * CurrentStatePtr;
    };
}
