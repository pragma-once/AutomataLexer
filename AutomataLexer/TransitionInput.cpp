#include "TransitionInput.h"

#include <stdexcept>
#include <utility>

namespace AutomataLexer
{
    TransitionInput::TransitionInput(const std::string& Str)
    {
        if (Str.length() == 0)
            throw std::logic_error("Cannot construct a TransitionInput with an empty string.");
        DataPtr = new StringData(Str);
    }

    TransitionInput::TransitionInput(char Ch) : DataPtr(new CharData(Ch))
    {
    }

    TransitionInput::TransitionInput(char Min, char Max)
    {
        if (Max < Min)
        {
            char temp = Max;
            Max = Min;
            Min = temp;
        }
        DataPtr = new CharRangeData(Min, Max);
    }

    TransitionInput::~TransitionInput()
    {
        if (DataPtr != nullptr) // In case the object has moved by the move constructor
            delete DataPtr;
    }

    TransitionInput::TransitionInput(const TransitionInput& Operand) noexcept
    {
        DataPtr = Operand.DataPtr->Clone();
    }

    TransitionInput::TransitionInput(TransitionInput&& Operand) noexcept
    {
        DataPtr = nullptr; // Checked by the destructor
        std::swap(DataPtr, Operand.DataPtr);
    }

    TransitionInput& TransitionInput::operator=(TransitionInput Operand) noexcept
    {
        std::swap(DataPtr, Operand.DataPtr);
        return *this;
    }

    int TransitionInput::Read(const std::string& Text, int Index)
    {
        return DataPtr->Read(Text, Index);
    }

    TransitionInput::StringData::StringData(const std::string& Expectation) : Expectation(Expectation) {}
    TransitionInput::CharRangeData::CharRangeData(char Min, char Max) : Min(Min), Max(Max) {}
    TransitionInput::CharData::CharData(char Expectation) : Expectation(Expectation) {}

    TransitionInput::Data * TransitionInput::StringData::Clone()    { return new StringData(Expectation); }
    TransitionInput::Data * TransitionInput::CharRangeData::Clone() { return new CharRangeData(Min, Max); }
    TransitionInput::Data * TransitionInput::CharData::Clone()      { return new CharData(Expectation);   }

    int TransitionInput::StringData::Read(const std::string& Text, int Index)
    {
        bool match = true;
        for (int i = 0; i < Expectation.length(); i++)
        {
            int j = Index + i;
            if (j > Text.length() || Text[j] != Expectation[i])
            {
                match = false;
                break;
            }
        }
        if (match)
            return Index + Expectation.length();
        return Index;
    }

    int TransitionInput::CharRangeData::Read(const std::string& Text, int Index)
    {
        if (Min <= Text[Index] && Text[Index] <= Max)
            return Index + 1;
        return Index;
    }

    int TransitionInput::CharData::Read(const std::string& Text, int Index)
    {
        if (Text[Index] == Expectation)
            return Index + 1;
        return Index;
    }
}
