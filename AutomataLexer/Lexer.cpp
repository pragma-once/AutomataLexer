#include "Lexer.h"

#include <algorithm>
#include <stdexcept>

namespace AutomataLexer
{
    Lexer::Lexer() : StartStateName("")
    {
    }

    inline void Lexer::AddTransition(std::string FromState,
                                     std::initializer_list<TransitionInput> InputSet,
                                     std::string ToState,
                                     std::initializer_list<std::variant<TokenReturnAction, MessageAction>> Actions)
    {
        AddTransition(
            FromState,
            (std::vector<TransitionInput>)InputSet,
            ToState,
            (std::vector<std::variant<TokenReturnAction, MessageAction>>)Actions
        );
    }

    void Lexer::AddTransition(std::string FromState,
                              std::vector<TransitionInput> InputSet,
                              std::string ToState,
                              std::vector<std::variant<TokenReturnAction, MessageAction>> Actions)
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

        auto actions_ptr = std::make_shared<std::vector<std::variant<TokenReturnAction, MessageAction>>>(Actions);

        auto& state = States[FromState];
        auto& transitions = state.Transitions;
        int j = 0;
        for (int i = 0; i < transitions.size(); i++)
        {
            if (std::get<0>(transitions[i]).GetLength() == 1)
                break;
            while (InputSet[j].GetLength() > std::get<0>(transitions[i]).GetLength())
                transitions.insert(transitions.begin() + i, std::make_tuple(InputSet[j++], dest_state_ptr, actions_ptr));
        }
        for (; j < InputSet.size(); j++)
            transitions.push_back(std::make_tuple(InputSet[j], dest_state_ptr, actions_ptr));
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

        std::string current_state = StartStateName;
        int stored_text_start = 0;
        for (int i = 0; i < Text.length(); i++)
        {
            auto state = States[current_state];
            for (auto transition : state.Transitions)
            {
                int j = std::get<0>(transition).Read(Text, i);
                if (i != j)
                {
                    current_state = *std::get<1>(transition);
                    CharacterPosition start_position; // TODO
                    CharacterPosition current_position; // TODO
                    for (auto& action : *std::get<2>(transition))
                    {
                        auto type_index = action.index();
                        if (type_index == 0) // Token return
                        {
                            Token token;
                            auto return_action = get<TokenReturnAction>(action);
                            token.StartPosition = start_position;
                            //token.EndPosition = current_position - return_action.Offset; // TODO
                            // TODO
                            tokens.push_back(token);
                        }
                        else if (type_index == 1) // Message
                        {
                            Message message;
                            // TODO
                            messages.push_back(message);
                        }
                    }
                    j = i;
                }
            }
        }

        return std::make_tuple(tokens, messages, success);
    }

    Lexer::StateInfo::StateInfo() : IsFinal(false) {}
}
