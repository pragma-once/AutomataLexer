#pragma once

#include <string>

#include "CharacterPosition.h"

namespace AutomataLexer
{
    class Message
    {
        public:

        /// @brief The start position of the character collection when the message was created.
        CharacterPosition StartPosition;
        /// @brief The position where the message was created.
        CharacterPosition Position;

        /// @brief The type of message, can be Error, Warning, or any string.
        std::string Type;
        /// @brief The actual message.
        std::string Content;
    };
}
