#include "Lexer.h"

#include <algorithm>
#include <stdexcept>

namespace AutomataLexer
{
    Lexer::Lexer() : StartStateName("")
    {
    }

    inline void Lexer::AddTransition(std::string FromState, std::initializer_list<TransitionInput> InputSet, std::string ToState)
    {
        AddTransition(FromState, (std::vector<TransitionInput>)InputSet, ToState);
    }

    void Lexer::AddTransition(std::string FromState, std::vector<TransitionInput> InputSet, std::string ToState)
    {
        if (FromState.length() == 0 || ToState.length() == 0)
            throw std::logic_error("Cannot name a state with an empty string.");

        if (StartStateName == "")
            StartStateName = FromState;

        std::sort(InputSet.begin(), InputSet.end(), [](TransitionInput& a, TransitionInput& b) {
            return a.GetLength() > b.GetLength();
        });

        auto& dest_state_ptr = StringPointers[ToState];
        if (!dest_state_ptr)
            dest_state_ptr = std::make_shared<std::string>(ToState);

        auto& state = States[FromState];
        auto& transitions = state.Transitions;
        int j = 0;
        for (int i = 0; i < transitions.size(); i++)
        {
            if (std::get<0>(transitions[i]).GetLength() == 1)
                break;
            while (InputSet[j].GetLength() > std::get<0>(transitions[i]).GetLength())
                transitions.insert(transitions.begin() + i, std::make_tuple(InputSet[j++], dest_state_ptr));
        }
        for (; j < InputSet.size(); j++)
            transitions.push_back(std::make_tuple(InputSet[j], dest_state_ptr));
    }

    void Lexer::MakeFinal(std::string State)
    {
        if (State.length() == 0)
            throw std::logic_error("Cannot name a state with an empty string.");

        States[State].IsFinal = true;
    }

    std::tuple<std::vector<Token>, std::vector<Message>, bool> Lexer::Process(std::string Text)
    {
        std::vector<Token> tokens;
        std::vector<Message> messages;
        bool success;

        // TODO

        return std::make_tuple(tokens, messages, success);
    }

    Lexer::StateInfo::StateInfo() : IsFinal(false) {}
}
