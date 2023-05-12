#pragma once

#include <string>

namespace AutomataLexer
{
    class TokenReturnAction
    {
        public:

        int Offset;
        std::string Type;
    };
}
