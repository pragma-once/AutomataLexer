#pragma once

#include <initializer_list>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

#include "Message.h"
#include "MessageAction.h"
#include "Token.h"
#include "TokenReturnAction.h"
#include "TransitionInput.h"

namespace AutomataLexer
{
    class Lexer
    {
        public:

        Lexer();
        /// The first FromState added will be the start state.
        void AddTransition(std::string FromState,
                           std::initializer_list<TransitionInput> InputSet,
                           std::string ToState,
                           std::initializer_list<std::variant<TokenReturnAction, MessageAction>> Actions
                                = std::initializer_list<std::variant<TokenReturnAction, MessageAction>>());
        /// The first FromState added will be the start state.
        void AddTransition(std::string FromState,
                           std::vector<TransitionInput> InputSet,
                           std::string ToState,
                           std::vector<std::variant<TokenReturnAction, MessageAction>> Actions
                                = std::vector<std::variant<TokenReturnAction, MessageAction>>());
        void MakeFinal(std::string State);
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

        class StateInfo
        {
            public:

            bool IsFinal;
            std::vector<std::tuple<
                    TransitionInput,
                    std::shared_ptr<std::string>,
                    std::shared_ptr<std::vector<std::variant<TokenReturnAction, MessageAction>>>
                >> Transitions;

            StateInfo();
        };

        std::map<std::string, StateInfo> States;
        std::string StartStateName;
        std::map<std::string, std::shared_ptr<std::string>> StringPointers;
    };
}
