#pragma once

#include <string>

#include "CharacterPosition.h"

namespace AutomataLexer
{
    class Token
    {
        public:

        CharacterPosition StartPosition;
        CharacterPosition EndPosition;

        /// @brief The type of the token. Examples: "operator_less_than_or_equal", "identifier", "integer"
        std::string Type;
        /// @brief The characters collected for the token. Examples: "<=", "_MyIdentifier_01", "255"
        std::string Text;
    };
}
