#pragma once

#include <string>

class ParseError : public std::runtime_error {
    public:
        ParseError(const std::string& message, int line, int column) : 
            std::runtime_error("StandupScript error (parsing) at " + std::to_string(line) + ":" + std::to_string(column) + " - " + message),
            line(line), 
            column(column) {}

        int line;
        int column;
};