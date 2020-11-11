#pragma once

#include <initializer_list>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "Message.h"
#include "Token.h"
#include "TransitionInput.h"

namespace AutomataLexer
{
    class Lexer
    {
        public:

        Lexer();
        void AddTransition(std::string FromState, std::initializer_list<TransitionInput> InputSet, std::string ToState);
        void AddTransition(std::string FromState, std::vector<TransitionInput> InputSet, std::string ToState);
        /// @brief Processes a text.
        ///
        /// An easy way to use this function:
        /// auto [Tokens, Messages, Success] = MyStateMachine.Process(MyText);
        ///
        /// @param Text The text to be processed.
        /// @return A tuple containing 3 items:
        ///         Tokens,
        ///         Messages,
        ///         Success (Whether the state machine has reached the final state and stopped there)
        std::tuple<std::vector<Token>, std::vector<Message>, bool> Process(std::string Text);

        private:

        std::map<std::string, std::vector<std::tuple<TransitionInput, std::string>>> States;
        std::string * CurrentStateNamePtr;
        std::vector<std::tuple<TransitionInput, std::string>> * CurrentStatePtr;
    };
}
