#pragma once

#include <string>

class LexerError : public std::runtime_error {
    public:
        LexerError(std::string& message, int line, int column) :  
            std::runtime_error("StandupScript error (lexing) at " + std::to_string(line) + ":" + std::to_string(column) + " - " + message),
            line(line), 
            column(column) {}

        int line;
        int column;
};