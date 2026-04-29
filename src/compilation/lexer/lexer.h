#pragma once

#include <string>
#include <vector>

#include "tokens.h"

class Lexer {
    private:
        std::string input;
        int position = 0;
        int line = 1;
        int column = 1;
        std::vector<Token> tokens;

    public:
        Lexer(const std::string& input) : input(input) {}
        std::vector<Token> tokenize();

};
